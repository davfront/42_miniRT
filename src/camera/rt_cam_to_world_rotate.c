/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 14:14:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world_rotate(t_mat4 c2w, t_float dx, t_float dy, \
	t_float sensitivity)
{
	t_mat4	result;
	t_vec3	pivot;
	t_float	pivot_dist;

	pivot_dist = 100;
	result = c2w;
	pivot = vec3_add(rt_cam_pos(result), \
		vec3_scale(rt_cam_dir(result), pivot_dist));
	result = mat4_translate(result, vec3_scale(pivot, -1));
	if (dx)
		result = mat4_rotate_y(result, -dx * sensitivity);
	if (dy)
		result = mat4_rotate_axis(result, rt_cam_right(result), \
			dy * sensitivity);
	result = mat4_translate(result, vec3_scale(pivot, 1));
	return (result);
}
