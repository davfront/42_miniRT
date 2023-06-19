/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_obj_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/09 19:44:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_get_obj_hit(t_ray ray, t_obj *obj)
{
	if (!obj)
		return (rt_hit_default());
	if (obj->type == SPHERE)
		return (rt_get_sphere_hit(ray, obj));
	if (obj->type == PLANE)
		return (rt_get_plane_hit(ray, obj));
	return (rt_hit_default());
}
