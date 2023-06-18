/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_render_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 09:46:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	*rt_draw_frame_thread(void *tv)
{
	int			x;
	int			y;
	t_ray		ray;
	t_thread	*t;

	t = tv;
	x = ((WIN_WIDTH) * (t->id - 1) / 4);
	// x = 0;
	while (x < ((WIN_WIDTH) * t->id) / 4)
	// while (x < WIN_WIDTH)
	{
		// y = (WIN_HEIGHT * (t->id - 1) / 4);
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = rt_get_view_ray(t->data->cam, x, y);
			ray.hit = rt_get_closest_hit(t->data, ray);
			t->data->obj_per_pixel[x][y] = ray.hit.obj;
			if (ray.hit.obj)
				rt_viewer_draw_pixel(t->data, x, y, rt_get_hit_color(t->data, ray));
			y++;
		}
		x++;
	}
	return (tv);
}

int	rt_viewer_render_frame(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, \
		&data->img.len, &data->img.endian);
	for(int i = 0;i < 4;i++)
	{
		data->thread[i].id = i + 1;
		data->thread[i].data = data;
		pthread_create(&data->thread[i].thread, 0, rt_draw_frame_thread, &data->thread[i]);
	}
	for (int i = 0;i < 4; i++)
	{
		pthread_join(data->thread[i].thread, NULL);
	}
	// rt_draw_frame(data);
	// DEBUG("post thread create")
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = NULL;
	return (0);
}
