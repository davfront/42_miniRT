/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_render_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 19:15:23 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_viewer_render_frame(t_data *data)
{
	t_light	*light;

	light = data->lights;
	
	t_float	angle = 0.1;
    t_float cosAngle = cos(angle);
    t_float sinAngle = sin(angle);

    light->pos.x = light->pos.x * cosAngle + light->pos.z * sinAngle;
    light->pos.y = light->pos.y;
    light->pos.z = -light->pos.x * sinAngle + light->pos.z * cosAngle;

	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, \
		&data->img.len, &data->img.endian);
	rt_draw_frame(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = NULL;
	return (0);
}
