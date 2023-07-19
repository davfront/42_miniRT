/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cone_transformations.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 14:26:09 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tf	rt_get_cone_transformations(t_cone co)
{
	t_tf	tf;

	tf.move = co.center;
	tf.rotate = quat_from_vec3(vec3(0, 1, 0), co.axis);
	tf.scale = vec3(co.radius, co.height, co.radius);
	return (tf);
}
