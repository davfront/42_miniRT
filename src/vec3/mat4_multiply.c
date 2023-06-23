/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_multiply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/21 13:41:29 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_mat4	mat4_multiply(t_mat4 a, t_mat4 b)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j]
				= a.m[i][0] * b.m[0][j]
				+ a.m[i][1] * b.m[1][j]
				+ a.m[i][2] * b.m[2][j]
				+ a.m[i][3] * b.m[3][j];
			j++;
		}
		i++;
	}
	return (result);
}
