/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_drag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/13 16:26:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_on_dragstart(t_data *data)
{
	if (!data)
		return ;
	data->cam->c2w_temp = data->cam->c2w;
	if (data->ui.selected && data->ui.cs_helper_hovered != -1)
	{
		data->ui.selected->tf_down = data->ui.selected->tf;
		data->ui.cs_down = data->ui.cs;
		data->ui.cs_helper_selected = data->ui.cs_helper_hovered;
	}
}

void	rt_on_dragend(t_data *data)
{
	if (!data)
		return ;
	data->ui.cs_helper_selected = -1;
}

void	rt_on_drag(t_data *data)
{
	if (!data || !data->cam)
		return ;
	if (data->ui.selected && data->ui.cs_helper_selected != -1)
		rt_on_drag_cs_helper(data, data->ui.cs_helper_selected);
	else
		rt_cam_update_c2w(data, \
			rt_cam_to_world_rotate(data->cam->c2w_temp, \
			data->ui.mouse_dragged.x, -data->ui.mouse_dragged.y, M_PI / 500));
	data->ui.changed = 1;
}
