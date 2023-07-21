/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lowres_draw_step.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/20 12:04:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_lowres_tile_cast_ray(t_data *data, int tx, int ty, int step)
{
	int		x;
	int		y;
	t_ray	ray;

	x = tx * data->rdr.tile_size + step / data->rdr.tile_size;
	y = ty * data->rdr.tile_size + step % data->rdr.tile_size;
	if (x < WIN_WIDTH && y < WIN_HEIGHT && !data->rdr.buf[x][y].exact)
	{
		ray = rt_get_view_ray(*data->cam, x, y);
		ray.hit = rt_get_closest_hit(data, ray);
		data->rdr.buf[x][y].color = rt_get_hit_color(data, ray);
		data->rdr.buf[x][y].obj = ray.hit.obj;
		data->rdr.buf[x][y].exact = 1;
	}
}

static void	rt_lowres_tile_complete(t_data *data, int tx, int ty)
{
	int		x;
	int		y;
	t_buf	buf;

	ft_bzero(&buf, sizeof(buf));
	y = ty * data->rdr.tile_size;
	while (y < (ty + 1) * data->rdr.tile_size && y < WIN_HEIGHT)
	{
		x = tx * data->rdr.tile_size;
		if (x < WIN_WIDTH && data->rdr.buf[x][y].exact)
			buf = data->rdr.buf[x][y];
		while (x < (tx + 1) * data->rdr.tile_size && x < WIN_WIDTH)
		{
			if (data->rdr.buf[x][y].exact)
				buf = data->rdr.buf[x][y];
			else
			{
				data->rdr.buf[x][y] = buf;
				data->rdr.buf[x][y].exact = 0;
			}
			x++;
		}
		y++;
	}
}

static void	rt_lowres_tile_draw(t_data *data, int tx, int ty)
{
	int		x;
	int		y;
	t_buf	buf;
	t_rgb	color;

	ft_bzero(&buf, sizeof(buf));
	y = ty * data->rdr.tile_size;
	while (y < (ty + 1) * data->rdr.tile_size && y < WIN_HEIGHT)
	{
		x = tx * data->rdr.tile_size;
		while (x < (tx + 1) * data->rdr.tile_size && x < WIN_WIDTH)
		{
			buf = data->rdr.buf[x][y];
			color = buf.color;
			if (buf.obj && buf.obj == data->ui.selected)
				color = rgb_mix(color, rgb(255, 255, 255), 0.1);
			rt_viewer_set_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	rt_lowres_draw_step(t_data *data, int step)
{
	int		tx;
	int		ty;

	tx = 0;
	while (tx <= WIN_WIDTH / data->rdr.tile_size)
	{
		ty = 0;
		while (ty <= WIN_HEIGHT / data->rdr.tile_size)
		{
			rt_lowres_tile_cast_ray(data, tx, ty, step);
			if (data->rdr.tile_size > 1)
				rt_lowres_tile_complete(data, tx, ty);
			rt_lowres_tile_draw(data, tx, ty);
			ty++;
		}
		tx++;
	}
}

void	*rt_lowres_draw_step_thread(void *tv)
{
	t_thread	*t;
	int			tx;
	int			ty;

	t = tv;
	tx = 0;
	while (tx <= WIN_WIDTH / t->data->rdr.tile_size)
	{
		if (tx % THREAD_NB == t->id - 1)
		{
			ty = 0;
			while (ty <= WIN_HEIGHT / t->data->rdr.tile_size)
			{
				rt_lowres_tile_cast_ray(t->data, tx, ty, t->data->rdr.step);
				if (t->data->rdr.tile_size > 1)
					rt_lowres_tile_complete(t->data, tx, ty);
				rt_lowres_tile_draw(t->data, tx, ty);
				ty++;
			}
		}
		tx++;
	}
	return (tv);
}
