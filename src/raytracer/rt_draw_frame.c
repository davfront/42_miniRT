/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/25 14:10:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define	STEP_MAX	3

static void	rt_clear_buffer(t_data *data)
{
	ft_bzero(data->buf, sizeof(t_buf) * WIN_WIDTH * WIN_HEIGHT);
}

static void	rt_cast_rays(t_data *data, int step)
{
	int		x;
	int		y;
	t_ray	ray;
	int		tile;

	if (step < 0 || step > STEP_MAX - 1)
		step = 0;
	tile = (int)pow(2, STEP_MAX - step);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (x % tile == 0 && y % tile == 0 && !data->buf[x][y].done)
			{
				ray = rt_get_view_ray(*data->cam, x, y);
				ray.hit = rt_get_closest_hit(data, ray);
				if (ray.hit.obj)
				{
					data->buf[x][y].color = rt_get_hit_color(data, ray);
					data->buf[x][y].done = 1;
				}
			}
			y++;
		}
		x++;
	}
}

void	rt_draw_tile(t_data *data, int t_size, int t_idx, int t_idy)
{
	int		x;
	int		y;
	t_rgb	c[2][2];
	// t_rgb	cy[2];
	t_rgb	cxy;
	t_float	dx;
	t_float	dy;

	c[0][0] = data->buf[t_idx * t_size][t_idy * t_size].color;

	c[1][0] = data->buf[t_idx * t_size][t_idy * t_size].color;
	if ((t_idx + 1) * t_size < WIN_WIDTH)
		c[1][0] = data->buf[(t_idx + 1) * t_size][t_idy * t_size].color;

	c[0][1] = data->buf[t_idx * t_size][t_idy * t_size].color;
	if ((t_idy + 1) * t_size < WIN_HEIGHT)
		c[0][1] = data->buf[t_idx * t_size][(t_idy + 1) * t_size].color;

	c[1][1] = data->buf[t_idx * t_size][t_idy * t_size].color;
	if ((t_idx + 1) * t_size < WIN_WIDTH && (t_idy + 1) * t_size < WIN_HEIGHT)
		c[1][1] = data->buf[(t_idx + 1) * t_size][(t_idy + 1) * t_size].color;

	x = t_idx * t_size;
	while (x < (t_idx + 1) * t_size && x < WIN_WIDTH)
	{
		dx = (t_float)x / t_size - t_idx; 
		y = t_idy * t_size;
		while (y < (t_idy + 1) * t_size && y < WIN_WIDTH)
		{
			dy = (t_float)y / t_size - t_idy; 
			cxy.r = (1.0 - dy) * ((1.0 - dx) * c[0][0].r + dx * c[1][0].r) + dy * ((1.0 - dx) * c[0][1].r + dx * c[1][1].r);
			cxy.g = (1.0 - dy) * ((1.0 - dx) * c[0][0].g + dx * c[1][0].g) + dy * ((1.0 - dx) * c[0][1].g + dx * c[1][1].g);
			cxy.b = (1.0 - dy) * ((1.0 - dx) * c[0][0].b + dx * c[1][0].b) + dy * ((1.0 - dx) * c[0][1].b + dx * c[1][1].b);
			rt_viewer_draw_pixel(data, x, y, cxy);
			y++;
		}
		x++;
	}
}

void	rt_draw_tiles(t_data *data, int step)
{
	int		x;
	int		y;
	int		tile_size;

	if (step < 0 || step > STEP_MAX - 1)
		step = 0;
	tile_size = (int)pow(2, STEP_MAX - step);
	x = 0;
	while (x < WIN_WIDTH / tile_size)
	{
		y = 0;
		while (y < WIN_HEIGHT / tile_size)
		{
			rt_draw_tile(data, tile_size, x, y);
			y++;
		}
		x++;
	}
}

void	rt_draw_frame(t_data *data)
{
	if (data->ui.changed)
	{
		data->buf_step = 0;
		rt_clear_buffer(data);
	}
	if (data->buf_step <= STEP_MAX - 1)
		rt_cast_rays(data, data->buf_step);
	rt_draw_tiles(data, data->buf_step);
	if (data->buf_step < STEP_MAX - 1)
		data->buf_step++;
	data->ui.changed = 0;
}
