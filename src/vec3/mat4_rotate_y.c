/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate_y.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 09:34:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_rotate_y(t_mat4 m, t_float a)
{
	t_float	cos_a;
	t_float	sin_a;
	t_mat4	rotate;

	cos_a = cos(a);
	sin_a = sin(a);
	rotate = mat4_identity();
	rotate.m[0][0] = cos_a;
	rotate.m[0][2] = sin_a;
	rotate.m[2][0] = -sin_a;
	rotate.m[2][2] = cos_a;
	return (mat4_multiply(m, rotate));
}
