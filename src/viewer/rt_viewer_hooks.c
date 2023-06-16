/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/06 14:54:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_key_hook(int key, t_data *data)
{
	if (key == KEY_ESC)
		rt_viewer_on_close(data);
	if (key == KEY_LEFT)
	{
		if (data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT])
		{
			data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]->sphere.center.z -= 1; 
		}
	}
	if (key == KEY_RIGHT)
	{
		if (data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT])
		{
			data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]->sphere.center.z += 1; 
		}
	}
	return (0);
}

static int	rt_viewer_on_mouse_move(int x, int y, t_data *data)
{
	(void)data;
	t_rgb	color = rgb_int(0x00303030);
	if (data->obj_per_pixel[x][y] && !data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT])
	{
		if (!data->obj_per_pixel[x][y]->selected)
		{
			data->obj_per_pixel[x][y]->selected = 1;
			data->obj_per_pixel[x][y]->sphere.color = rgb_add(data->obj_per_pixel[x][y]->sphere.color, color);
			data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT] = data->obj_per_pixel[x][y];
			DEBUG("%p", data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]);
		}
	}
	else if (data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT] && data->obj_per_pixel[x][y] != data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT])
	{
		DEBUG("%p", data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]);
		data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]->sphere.color = rgb_subtract(data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]->sphere.color, color);
		data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT]->selected = 0;
		data->obj_per_pixel[WIN_WIDTH][WIN_HEIGHT] = NULL;
	}

	return (0);
}

void	rt_viewer_hooks(t_data *data)
{
	mlx_key_hook(data->win, rt_key_hook, data);
	mlx_hook(data->win, 17, 1L << 0, rt_viewer_on_close, data);
	// mlx_hook(data->win, 2, 1L << 0, rt_viewer_on_keydown, data);
	// mlx_hook(data->win, 3, 1L << 1, rt_viewer_on_keyup, data);
	// mlx_hook(data->win, 4, 1L << 2, rt_viewer_on_mouse_down, data);
	// mlx_hook(data->win, 5, 1L << 3, rt_viewer_on_mouse_up, data);
	mlx_hook(data->win, 6, 1L << 6, rt_viewer_on_mouse_move, data);
}
