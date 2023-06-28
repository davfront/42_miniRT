/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 17:02:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world(t_vec3 cam_pos, t_vec3 cam_dir)
{
	t_vec3	up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	top;
	t_mat4	result;

	up = vec3(0, 1, 0);
	if (vec3_length_squared(vec3_cross(up, cam_dir)) == 0)
		up = vec3(1, 0, 0);
	forward = vec3_scale(cam_dir, -1);
	right = vec3_normalize(vec3_cross(up, forward));
	top = vec3_normalize(vec3_cross(forward, right));
	result = mat4_identity();
	result = mat4_translate(result, cam_pos);
	result.m[0][0] = right.x;
	result.m[1][0] = right.y;
	result.m[2][0] = right.z;
	result.m[0][1] = top.x;
	result.m[1][1] = top.y;
	result.m[2][1] = top.z;
	result.m[0][2] = forward.x;
	result.m[1][2] = forward.y;
	result.m[2][2] = forward.z;
	return (result);
}
