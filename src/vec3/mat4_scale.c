/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/13 15:36:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_scale(t_mat4 m, t_vec3 v)
{
	t_mat4	result;

	result = m;
	result.m[0][0] *= v.x;
	result.m[1][1] *= v.y;
	result.m[2][2] *= v.z;
	return (result);
}
