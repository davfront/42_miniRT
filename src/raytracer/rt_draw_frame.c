/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/02 21:33:11 by dapereir         ###   ########.fr       */
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
		rt_lowres_draw_step(data, data->rdr.step);
	if (data->rdr.step < data->rdr.step_max)
		data->rdr.step++;
	data->ui.changed = 0;
}
