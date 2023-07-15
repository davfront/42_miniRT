/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_sphere_transformations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 14:16:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tf	rt_get_sphere_transformations(t_sphere sp)
{
	t_tf	tf;

	tf.move = sp.center;
	tf.rotate = quat_identity();
	tf.scale = vec3_scale(vec3(1, 1, 1), sp.radius);
	return (tf);
}
