/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_transformed_sphere.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 14:16:14 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	rt_get_transformed_sphere(t_obj obj)
{
	t_sphere	sp;

	sp = obj.sphere;
	sp.center = obj.tf.move;
	sp.radius = obj.tf.scale.x;
	return (sp);
}
