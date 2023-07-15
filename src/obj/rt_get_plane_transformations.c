/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_transformations.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 14:19:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tf	rt_get_plane_transformations(t_plane pl)
{
	t_tf	tf;

	tf.move = pl.point;
	tf.rotate = quat_from_vec3(vec3(0, 1, 0), pl.normal);
	tf.scale = vec3(1, 1, 1);
	return (tf);
}
