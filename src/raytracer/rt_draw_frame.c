/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/20 12:03:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_clear_buffer(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ft_bzero(&(data->rdr.buf[x][y]), sizeof(t_buf));
			y++;
		}
		x++;
	}
}

static void	rt_draw_buffer(t_data *data)
{
	int		x;
	int		y;
	t_buf	buf;
	t_rgb	color;

	ft_bzero(&buf, sizeof(buf));
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
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

void	rt_draw_frame(t_data *data)
{
	if (data->ui.changed)
		data->rdr.step = 0;
	if (data->rdr.step == 0)
	{
		rt_clear_buffer(data);
		if (LOW_RES_ENABLED)
			data->rdr.tile_size = rt_lowres_estimate_size(data);
		else
			data->rdr.tile_size = 1;
		data->rdr.step_max = data->rdr.tile_size * data->rdr.tile_size - 1;
	}
	if (data->rdr.step <= data->rdr.step_max)
		rt_viewer_thread_handler(data);
	else
		rt_draw_buffer(data);
	if (data->rdr.step <= data->rdr.step_max)
		data->rdr.step++;
	data->ui.changed = 0;
}
