/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_cofactor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/03 14:46:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

static t_mat3	mat4_submatrix(t_mat4 m, int row, int col)
{
	t_mat3	result;
	int		sub_row;
	int		sub_col;
	int		i;
	int		j;

	sub_row = 0;
	i = 0;
	while (i < 4)
	{
		if (i != row)
		{
			sub_col = 0;
			j = 0;
			while (j < 4)
			{
				if (j != col)
					result.m[sub_row][sub_col++] = m.m[i][j];
				j++;
			}
			sub_row++;
		}
		i++;
	}
	return (result);
}

static t_float	mat3_determinant(t_mat3 m)
{
	t_float	det;

	det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) \
		- m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) \
		+ m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
	return (det);
}

t_mat4	mat4_cofactor(t_mat4 m)
{
	t_mat4	result;
	int		i;
	int		j;
	t_float	sub_det;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			sub_det = mat3_determinant(mat4_submatrix(m, i, j));
			if ((i + j) % 2 == 0)
				result.m[i][j] = sub_det;
			else
				result.m[i][j] = -sub_det;
			j++;
		}
		i++;
	}
	return (result);
}
