/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/22 22:00:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_scale(t_mat4 m, t_float f)
{
	t_mat4	result;

	result = m;
	result.m[0][0] *= f;
	result.m[1][1] *= f;
	result.m[2][2] *= f;
	return (result);
}
