/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 16:20:23 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world_rotate(t_mat4 c2w, t_float dx, t_float dy, \
	t_float sensitivity)
{
	t_mat4	result;
	t_float	angle_y;
	t_float	angle_cam_right;
	t_quat	mouse_rot_y;
	t_quat	mouse_rot_right;

	result = c2w;
	angle_y = -dx * sensitivity;
	mouse_rot_y = quat_from_axis_angle(vec3(0, 1, 0), angle_y);
	result = mat4_multiply(mat4_from_quat(mouse_rot_y), result);
	angle_cam_right = dy * sensitivity;
	mouse_rot_right = quat_from_axis_angle(rt_cam_right(result), \
		angle_cam_right);
	result = mat4_multiply(mat4_from_quat(mouse_rot_right), result);
	return (result);
}
