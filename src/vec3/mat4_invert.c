/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_invert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/03 14:55:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

static t_float	mat4_determinant(t_mat4 m)
{
	t_float	det;

	det = m.m[0][0] \
			* (m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) \
			- m.m[1][2] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) \
			+ m.m[1][3] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1])) \
		- m.m[0][1] \
			* (m.m[1][0] * (m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2]) \
			- m.m[1][2] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) \
			+ m.m[1][3] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0]))
		+ m.m[0][2] \
			* (m.m[1][0] * (m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1]) \
			- m.m[1][1] * (m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0]) \
			+ m.m[1][3] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0])) \
		- m.m[0][3] \
			* (m.m[1][0] * (m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1]) \
			- m.m[1][1] * (m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0]) \
			+ m.m[1][2] * (m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0]));
	return (det);
}

t_mat4	mat4_invert(t_mat4 m)
{
	t_mat4	result;
	t_mat4	adj;
	t_float	det;
	int		i;
	int		j;

	det = mat4_determinant(m);
	if (det == 0)
		return (m);
	adj = mat4_transpose(mat4_cofactor(m));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = adj.m[i][j] / det;
			j++;
		}
		i++;
	}
	return (result);
}
