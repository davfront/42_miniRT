/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 10:59:06 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_rotate_x(t_mat4 m, t_float a)
{
	t_float	cos_a;
	t_float	sin_a;
	t_mat4	rotate;

	cos_a = cos(a);
	sin_a = sin(a);
	rotate = mat4_identity();
	rotate.m[1][1] = cos_a;
	rotate.m[1][2] = -sin_a;
	rotate.m[2][1] = sin_a;
	rotate.m[2][2] = cos_a;
	return (mat4_multiply_rev(m, rotate));
}
