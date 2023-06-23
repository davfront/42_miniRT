/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_from_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 15:58:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_quat	quat_from_vec3(t_vec3 v0, t_vec3 v1)
{
	t_vec3	axis;
	t_float	cos_half_angle;
	t_float	half_angle;
	t_float	f;

	v0 = vec3_normalize(v0);
	v1 = vec3_normalize(v1);
	cos_half_angle = vec3_dot(v1, v0);
	if (cos_half_angle >= 1)
		return (quat(1, 0, 0, 0));
	half_angle = acos(cos_half_angle);
	axis = vec3_normalize(vec3_cross(v0, v1));
	f = sin(half_angle) / vec3_length(axis);
	return (quat(cos_half_angle, axis.x * f, axis.y * f, axis.z * f));
}
