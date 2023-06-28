/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_from_axis_angle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 15:58:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_quat	quat_from_axis_angle(t_vec3 axis, t_float angle)
{
	t_float	half_angle;
	t_float	sin_half_angle;
	t_vec3	normalized_axis;
	t_quat	result;

	half_angle = angle / 2;
	sin_half_angle = sinf(half_angle);
	normalized_axis = vec3_normalize(axis);
	result.w = cosf(half_angle);
	result.x = normalized_axis.x * sin_half_angle;
	result.y = normalized_axis.y * sin_half_angle;
	result.z = normalized_axis.z * sin_half_angle;
	return (result);
}
