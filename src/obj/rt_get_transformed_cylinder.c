/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_transformed_cylinder.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/15 14:29:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	rt_get_transformed_cylinder(t_obj obj)
{
	t_cylinder	cy;

	cy = obj.cylinder;
	cy.center = obj.tf.move;
	cy.axis = mat4_multiply_axis(mat4_from_quat(obj.tf.rotate), vec3(0, 1, 0));
	cy.radius = obj.tf.scale.x;
	cy.height = obj.tf.scale.y * 2;
	return (cy);
}
