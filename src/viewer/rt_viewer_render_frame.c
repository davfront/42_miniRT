/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_render_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/06 14:33:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_viewer_render_frame(t_data *data)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, \
		&data->img.len, &data->img.endian);
	rt_viewer_thread_handler(data);
	rt_ui_selected(data);
	rt_ui_help_bg(data);
	rt_ui_frame_progress(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = NULL;
	gettimeofday(&end, NULL);
	rt_help(data);
	rt_set_fps(data, start, end);
	return (0);
}
