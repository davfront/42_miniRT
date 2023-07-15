/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_transformed_plane.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/15 14:29:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	rt_get_transformed_plane(t_obj obj)
{
	t_plane	pl;

	pl = obj.plane;
	pl.point = obj.tf.move;
	pl.normal = mat4_multiply_axis(\
		mat4_from_quat(obj.tf.rotate), vec3(0, 1, 0));
	return (pl);
}
