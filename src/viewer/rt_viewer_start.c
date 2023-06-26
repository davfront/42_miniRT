/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:03:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 16:30:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_viewer_start(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		rt_delete(data);
		rt_error_exit(data, "Minilibx initialization failed");
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, data->title);
	ft_printf("[%s] File opened\n", data->title);
	rt_viewer_hooks(data);
	mlx_loop_hook(data->mlx, rt_viewer_render_frame, data);
	mlx_loop(data->mlx);
}
