/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_on_mouse_events.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/02 16:25:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_viewer_on_mouse_down(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_SCROLL_UP)
	{
		data->cam->c2w = rt_cam_to_world_translate(data->cam->c2w, \
			vec3(0, 0, 1), 10);
		data->ui.changed = 1;
	}
	if (button == MOUSE_SCROLL_DOWN)
	{
		data->cam->c2w = rt_cam_to_world_translate(data->cam->c2w, \
			vec3(0, 0, -1), 10);
		data->ui.changed = 1;
	}
	if (button == MOUSE_LEFT)
		data->ui.mouse_left_btn = 1;
	if (button == MOUSE_RIGHT)
		data->ui.mouse_right_btn = 1;
	data->ui.mouse_x0 = x;
	data->ui.mouse_y0 = y;
	data->ui.mouse_dx = 0;
	data->ui.mouse_dy = 0;
	data->cam->c2w_temp = data->cam->c2w;
	return (0);
}

int	rt_viewer_on_mouse_up(int button, int x, int y, t_data *data)
{
	data->cam->c2w_temp = data->cam->c2w;
	data->ui.mouse_dx = x - data->ui.mouse_x0;
	data->ui.mouse_dy = y - data->ui.mouse_y0;
	if (button == MOUSE_LEFT)
		data->ui.mouse_left_btn = 0;
	if (button == MOUSE_LEFT && !data->ui.mouse_dx && !data->ui.mouse_dy)
	{
		if (data->ui.selected == data->rdr.buf[x][y].obj)
			data->ui.selected = NULL;
		else
			data->ui.selected = data->rdr.buf[x][y].obj;
	}
	if (button == MOUSE_RIGHT)
		data->ui.mouse_right_btn = 0;
	data->ui.mouse_x0 = 0;
	data->ui.mouse_y0 = 0;
	data->ui.mouse_dx = 0;
	data->ui.mouse_dy = 0;
	return (0);
}

int	rt_viewer_on_mouse_move(int x, int y, t_data *data)
{
	data->ui.mouse_dx = x - data->ui.mouse_x0;
	data->ui.mouse_dy = y - data->ui.mouse_y0;
	data->cam->c2w = data->cam->c2w_temp;
	if (data->ui.mouse_left_btn)
	{
		data->cam->c2w = rt_cam_to_world_rotate(data->cam->c2w_temp, \
			data->ui.mouse_dx, -data->ui.mouse_dy, M_PI / 500);
		data->ui.changed = 1;
	}
	if (data->ui.mouse_right_btn)
	{
		data->cam->c2w = rt_cam_to_world_translate(data->cam->c2w_temp, \
			vec3(data->ui.mouse_dx, -data->ui.mouse_dy, 0), 0.1);
		data->ui.changed = 1;
	}
	return (0);
}
