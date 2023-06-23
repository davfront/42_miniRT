/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/21 14:15:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
		rt_viewer_on_close(data);
	return (0);
}

void	rt_viewer_hooks(t_data *data)
{
	mlx_key_hook(data->win, rt_key_hook, data);
	mlx_hook(data->win, 17, 1L << 0, rt_viewer_on_close, data);
	// mlx_hook(data->win, 2, 1L << 0, rt_viewer_on_keydown, data);
	// mlx_hook(data->win, 3, 1L << 1, rt_viewer_on_keyup, data);
	mlx_hook(data->win, 4, 1L << 2, rt_viewer_on_mouse_down, data);
	mlx_hook(data->win, 5, 1L << 3, rt_viewer_on_mouse_up, data);
	mlx_hook(data->win, 6, 1L << 6, rt_viewer_on_mouse_move, data);
}
