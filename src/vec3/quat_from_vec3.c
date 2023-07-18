/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_from_vec3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 00:07:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_quat	quat_from_vec3(t_vec3 v0, t_vec3 v1)
{
	t_vec3	axis;
	t_float	angle;
	t_float	half_angle;
	t_float	f;

	axis = vec3_cross(v0, v1);
	if (vec3_length(axis) < 1e-6)
	{
		if (vec3_dot(v0, v1) < 0)
			return (quat(0, 0, 0, 1));
		return (quat_identity());
	}
	axis = vec3_normalize(axis);
	angle = acos(vec3_dot(v0, v1));
	half_angle = angle / 2;
	f = sin(half_angle);
	return (quat(cos(half_angle), axis.x * f, axis.y * f, axis.z * f));
}
