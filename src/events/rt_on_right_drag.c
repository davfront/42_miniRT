/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_right_drag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 11:09:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_on_right_dragstart(t_data *data)
{
	data->cam->c2w_temp = data->cam->c2w;
}

void	rt_on_right_dragend(t_data *data)
{
	(void)data;
}

void	rt_on_right_drag(t_data *data)
{
	if (!data || !data->cam)
		return ;
	rt_cam_update_c2w(data, \
		rt_cam_to_world_translate(data->cam->c2w_temp, \
		vec3(data->ui.mouse_dragged.x, -data->ui.mouse_dragged.y, 0), 0.1));
	data->ui.changed = 1;
}
