/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_transformations.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 14:29:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tf	rt_get_cylinder_transformations(t_cylinder cy)
{
	t_tf	tf;

	tf.move = cy.center;
	tf.rotate = quat_from_vec3(vec3(0, 1, 0), cy.axis);
	tf.scale = vec3(cy.radius, cy.height / 2, cy.radius);
	return (tf);
}
