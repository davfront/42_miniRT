/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:44:12 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 10:20:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_quat	quat(t_float w, t_float x, t_float y, t_float z)
{
	t_quat	result;

	result.w = w;
	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
