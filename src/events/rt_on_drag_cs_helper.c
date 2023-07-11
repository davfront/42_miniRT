/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_drag_cs_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 15:14:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_on_drag_cs_helper_mov(t_data *data, int helper_id)
{
	t_vec3	v;
	t_vec3	arrow;
	t_vec3	dragged;
	t_float	arrow_len;

	if (!data)
		return ;
	v = rt_cs_helper_axis_in_obj(helper_id);
	if (!v.x && !v.y && !v.z)
		return ;
	arrow = vec3_subtract(px_to_vec3(data->ui.cs_down.helper_px[helper_id]), \
		px_to_vec3(data->ui.cs_down.helper_px[CS_ORIG]));
	dragged = px_to_vec3(data->ui.mouse_dragged);
	arrow_len = vec3_length(arrow);
	if (arrow_len <= CS_POINT_RAD * 2)
		return ;
	v = vec3_scale(v, \
		vec3_dot(arrow, dragged) / arrow_len \
		* -data->ui.cs_down.center.z * data->cam->tan_half_fov * 2 / WIN_HEIGHT \
		/ 10);
	data->ui.selected->mt = mat4_multiply_rev(\
		mat4_translate(mat4_identity(), v), \
		data->ui.selected->mt_temp);
}

static t_mat4	rt_obj_mt_rotate(t_mat4 mt, t_vec3 axis, t_float angle)
{
	t_mat4	result;
	t_mat4	m_rot;
	t_vec3	center;

	result = mt;
	center = mat4_multiply_vec3(result, vec3(0, 0, 0));
	result = mat4_translate(result, vec3_scale(center, -1));
	m_rot = mat4_rotate_axis(mat4_identity(), axis, angle);
	result = mat4_multiply_rev(m_rot, result);
	result = mat4_translate(result, center);
	return (result);
}

static void	rt_on_drag_cs_helper_rot(t_data *data, int helper_id)
{
	t_vec3	axis;
	t_vec3	from;
	t_vec3	to;
	t_float	angle;

	axis = rt_cs_helper_axis_in_obj(helper_id);
	if (!axis.x && !axis.y && !axis.z)
		return ;
	from = vec3_subtract(px_to_vec3(data->ui.cs_down.helper_px[helper_id]), \
		px_to_vec3(data->ui.cs_down.helper_px[CS_ORIG]));
	to = vec3_subtract(px_to_vec3(data->ui.mouse), \
		px_to_vec3(data->ui.cs_down.helper_px[CS_ORIG]));
	if (vec3_length(from) <= CS_POINT_RAD * 2 \
		|| vec3_length(to) <= CS_POINT_RAD * 2)
		return ;
	from = vec3_normalize(from);
	to = vec3_normalize(to);
	angle = acos(vec3_dot(from, to));
	if (vec3_cross(to, from).z < 0)
		angle *= -1;
	if (rt_cs_helper_axis_in_cam(data->ui.cs_down, helper_id).z < 0)
		angle *= -1;
	data->ui.selected->mt = \
		rt_obj_mt_rotate(data->ui.selected->mt_temp, axis, angle);
}

void	rt_on_drag_cs_helper(t_data *data, int helper_id)
{
	if (helper_id == CS_MOV_X \
		|| helper_id == CS_MOV_Y \
		|| helper_id == CS_MOV_Z)
		rt_on_drag_cs_helper_mov(data, helper_id);
	else if (helper_id == CS_ROT_X \
		|| helper_id == CS_ROT_Y \
		|| helper_id == CS_ROT_Z)
		rt_on_drag_cs_helper_rot(data, helper_id);
}
