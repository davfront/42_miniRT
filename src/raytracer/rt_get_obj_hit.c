/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_obj_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/20 12:33:50 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_get_obj_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	if (!obj)
		return (0);
	if (obj->type == SPHERE)
		return (rt_get_sphere_hit(ray, obj, t_max, hit));
	else if (obj->type == PLANE)
		return (rt_get_plane_hit(ray, obj, t_max, hit));
	else if (obj->type == CYLINDER)
		return (rt_get_cylinder_hit(ray, obj, t_max, hit));
	return (0);
}
