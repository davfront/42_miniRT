/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_transformed_cone.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/19 14:25:54 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone	rt_get_transformed_cone(t_obj obj)
{
	t_cone	co;

	co = obj.cone;
	co.center = obj.tf.move;
	co.axis = mat4_multiply_axis(mat4_from_quat(obj.tf.rotate), vec3(0, 1, 0));
	co.radius = obj.tf.scale.x;
	co.height = obj.tf.scale.y;
	return (co);
}
