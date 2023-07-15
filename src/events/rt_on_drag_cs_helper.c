/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_drag_cs_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 13:48:43 by dapereir         ###   ########.fr       */
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
	v = vec3_scale(v, vec3_dot(arrow, dragged) / arrow_len \
		* -data->ui.cs_down.center.z * data->cam->tan_half_fov \
		* 2 / WIN_HEIGHT);
	data->ui.selected->tf = data->ui.selected->tf_down;
	v = mat4_multiply_vec3(mat4_from_quat(data->ui.selected->tf.rotate), v);
	data->ui.selected->tf.move = vec3_add(data->ui.selected->tf.move, v);
}

static void	rt_on_drag_cs_helper_rot(t_data *data, int helper_id)
{
	t_vec3	axis;
	t_vec3	v[2];
	t_float	angle;
	t_quat	rot;

	axis = rt_cs_helper_axis_in_obj(helper_id);
	if (!axis.x && !axis.y && !axis.z)
		return ;
	v[0] = vec3_subtract(px_to_vec3(data->ui.cs_down.helper_px[helper_id]), \
		px_to_vec3(data->ui.cs_down.helper_px[CS_ORIG]));
	v[1] = vec3_subtract(px_to_vec3(data->ui.mouse), \
		px_to_vec3(data->ui.cs_down.helper_px[CS_ORIG]));
	if (fmin(vec3_length(v[0]), vec3_length(v[1])) <= CS_POINT_RAD * 2)
		return ;
	v[0] = vec3_normalize(v[0]);
	v[1] = vec3_normalize(v[1]);
	angle = acos(vec3_dot(v[0], v[1]));
	if (vec3_cross(v[0], v[1]).z > 0)
		angle *= -1;
	if (rt_cs_helper_axis_in_cam(data->ui.cs_down, helper_id).z < 0)
		angle *= -1;
	rot = quat_from_axis_angle(axis, angle);
	data->ui.selected->tf = data->ui.selected->tf_down;
	data->ui.selected->tf.rotate = \
		quat_multiply(data->ui.selected->tf.rotate, rot);
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
