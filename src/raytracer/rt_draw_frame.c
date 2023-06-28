/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 16:35:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_clear_buffer(t_data *data)
{
	ft_bzero(data->buf, sizeof(t_buf) * WIN_WIDTH * WIN_HEIGHT);
}

static void	rt_cast_rays_to_buffer(t_data *data, int step)
{
	int		tx;
	int		ty;
	int		x;
	int		y;
	t_ray	ray;

	tx = 0;
	while (tx < WIN_WIDTH / TILE_SIZE)
	{
		ty = 0;
		while (ty < WIN_HEIGHT / TILE_SIZE)
		{
			x = tx * TILE_SIZE + step / TILE_SIZE;
			y = ty * TILE_SIZE + step % TILE_SIZE;
			if (!data->buf[x][y].done)
			{
				ray = rt_get_view_ray(*data->cam, x, y);
				ray.hit = rt_get_closest_hit(data, ray);
				data->buf[x][y].color = rt_get_hit_color(data, ray);
				data->buf[x][y].done = 1;
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
	y = ty * TILE_SIZE;
	while (y < (ty + 1) * TILE_SIZE && y < WIN_HEIGHT)
	{
		x = tx * TILE_SIZE;
		if (data->buf[x][y].done)
			color = data->buf[x][y].color;
		while (x < (tx + 1) * TILE_SIZE && x < WIN_WIDTH)
		{
			if (data->buf[x][y].done)
				color = data->buf[x][y].color;
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
	while (tx < WIN_WIDTH / TILE_SIZE)
	{
		ty = 0;
		while (ty < WIN_HEIGHT / TILE_SIZE)
		{
			rt_draw_tile(data, tx, ty);
			ty++;
		}
		tx++;
	}
}

void	rt_draw_frame(t_data *data)
{
	if (data->ui.changed)
	{
		data->buf_step = 0;
		rt_clear_buffer(data);
	}
	if (data->buf_step < TILE_SIZE * TILE_SIZE)
		rt_cast_rays_to_buffer(data, data->buf_step);
	rt_draw_buffer(data);
	if (data->buf_step < TILE_SIZE * TILE_SIZE - 1)
		data->buf_step++;
	data->ui.changed = 0;
}
