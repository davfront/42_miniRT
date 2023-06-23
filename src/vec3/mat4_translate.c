/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 09:29:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_translate(t_mat4 m, t_vec3 v)
{
	t_mat4	translate;

	translate = mat4_identity();
	translate.m[0][3] += v.x;
	translate.m[1][3] += v.y;
	translate.m[2][3] += v.z;
	return (mat4_multiply(m, translate));
}
