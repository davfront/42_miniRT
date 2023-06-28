/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_from_quat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 15:59:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_from_quat(t_quat q)
{
	t_mat4	result;

	result = mat4_identity();
	result.m[0][0] = 1 - 2 * ((q.y * q.y) + (q.z * q.z));
	result.m[0][1] = 2 * ((q.x * q.y) - (q.w * q.z));
	result.m[0][2] = 2 * ((q.x * q.z) + (q.w * q.y));
	result.m[1][0] = 2 * ((q.x * q.y) + (q.w * q.z));
	result.m[1][1] = 1 - 2 * ((q.x * q.x) + (q.z * q.z));
	result.m[1][2] = 2 * ((q.y * q.z) - (q.w * q.x));
	result.m[2][0] = 2 * ((q.x * q.z) - (q.w * q.y));
	result.m[2][1] = 2 * ((q.y * q.z) + (q.w * q.x));
	result.m[2][2] = 1 - 2 * ((q.x * q.x) + (q.y * q.y));
	return (result);
}
