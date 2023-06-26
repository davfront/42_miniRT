/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate_axis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:46:45 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 14:16:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_rotate_axis(t_mat4 m, t_vec3 axis, float_t angle)
{
	t_mat4	result;
	t_quat	quat_rotate;

	result = m;
	quat_rotate = quat_from_axis_angle(axis, angle);
	result = mat4_multiply_rev(result, mat4_from_quat(quat_rotate));
	return (result);
}
