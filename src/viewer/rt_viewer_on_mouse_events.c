/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_on_mouse_events.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 11:02:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_viewer_on_mouse_down(int button, int x, int y, t_data *data)
{
	data->ui.mouse_down = px(x, y);
	data->ui.mouse_dragged.x = 0;
	data->ui.mouse_dragged.y = 0;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		rt_on_scroll(data, button == MOUSE_SCROLL_UP);
	if (button == MOUSE_LEFT)
	{
		data->ui.mouse_left_btn = 1;
		rt_on_dragstart(data);
	}
	if (button == MOUSE_RIGHT)
	{
		data->ui.mouse_right_btn = 1;
		rt_on_right_dragstart(data);
	}
	return (0);
}

int	rt_viewer_on_mouse_up(int button, int x, int y, t_data *data)
{
	data->ui.mouse = px(x, y);
	if (button == MOUSE_LEFT)
	{
		data->ui.mouse_left_btn = 0;
		rt_on_dragend(data);
	}
	if (button == MOUSE_RIGHT)
	{
		data->ui.mouse_right_btn = 0;
		rt_on_right_dragend(data);
	}
	if (button == MOUSE_LEFT \
		&& data->ui.mouse.x == data->ui.mouse_down.x \
		&& data->ui.mouse.y == data->ui.mouse_down.y)
		rt_on_click(data);
	return (0);
}

int	rt_viewer_on_mouse_move(int x, int y, t_data *data)
{
	data->ui.mouse = px(x, y);
	data->ui.mouse_dragged.x = data->ui.mouse.x - data->ui.mouse_down.x;
	data->ui.mouse_dragged.y = data->ui.mouse.y - data->ui.mouse_down.y;
	rt_on_mouse_move(data);
	if (data->ui.mouse_left_btn)
		rt_on_drag(data);
	if (data->ui.mouse_right_btn)
		rt_on_right_drag(data);
	return (0);
}
