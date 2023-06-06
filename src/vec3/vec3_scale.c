/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/06 21:29:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_scale(t_vec3 v, t_float f)
{
	t_vec3	result;

	result.x = v.x * f;
	result.y = v.y * f;
	result.z = v.z * f;
	return (result);
}
