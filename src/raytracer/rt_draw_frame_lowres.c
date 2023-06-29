/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame_lowres.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/29 14:44:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_clear_buffer(t_data *data)
{
	ft_bzero(data->rdr.buf, sizeof(t_buf) * WIN_WIDTH * WIN_HEIGHT);
}

static void	rt_cast_rays_to_buffer(t_data *data, int step)
{
	int		tx;
	int		ty;
	int		x;
	int		y;
	t_ray	ray;

	tx = 0;
	while (tx < WIN_WIDTH / data->rdr.tile_size)
	{
		ty = 0;
		while (ty < WIN_HEIGHT / data->rdr.tile_size)
		{
			x = tx * data->rdr.tile_size + step / data->rdr.tile_size;
			y = ty * data->rdr.tile_size + step % data->rdr.tile_size;
			if (!data->rdr.buf[x][y].done)
			{
				ray = rt_get_view_ray(*data->cam, x, y);
				ray.hit = rt_get_closest_hit(data, ray);
				data->rdr.buf[x][y].color = rt_get_hit_color(data, ray);
				data->rdr.buf[x][y].done = 1;
			}
			ty++;
		}
		tx++;
	}
}

void	rt_draw_tile(t_data *data, int tx, int ty)
{
	int		x;
	int		y;
	t_rgb	color;

	color = rgb(0, 0, 0);
	y = ty * data->rdr.tile_size;
	while (y < (ty + 1) * data->rdr.tile_size && y < WIN_HEIGHT)
	{
		x = tx * data->rdr.tile_size;
		if (data->rdr.buf[x][y].done)
			color = data->rdr.buf[x][y].color;
		while (x < (tx + 1) * data->rdr.tile_size && x < WIN_WIDTH)
		{
			if (data->rdr.buf[x][y].done)
				color = data->rdr.buf[x][y].color;
			rt_viewer_draw_pixel(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	rt_draw_buffer(t_data *data)
{
	int		tx;
	int		ty;

	tx = 0;
	while (tx < WIN_WIDTH / data->rdr.tile_size)
	{
		ty = 0;
		while (ty < WIN_HEIGHT / data->rdr.tile_size)
		{
			rt_draw_tile(data, tx, ty);
			ty++;
		}
		tx++;
	}
}

void	rt_draw_frame_lowres(t_data *data)
{
	data->rdr.tile_size = TILE_SIZE;
	data->rdr.step_max = data->rdr.tile_size * data->rdr.tile_size - 1;
	if (data->ui.changed)
	{
		data->rdr.step = 0;
		rt_clear_buffer(data);
	}
	if (data->rdr.step <= data->rdr.step_max)
		rt_cast_rays_to_buffer(data, data->rdr.step);
	rt_draw_buffer(data);
	if (data->rdr.step < data->rdr.step_max)
		data->rdr.step++;
	data->ui.changed = 0;
}
