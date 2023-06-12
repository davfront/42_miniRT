/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:15 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 09:29:09 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	result;
	t_float	d;

	d = vec3_dot(v, n) * 2;
	result = vec3_subtract(v, vec3_scale(n, d));
	return (result);
}
