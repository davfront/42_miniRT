/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/12 18:45:21 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float rt_find_plane_coef(t_plane pl)
{
	return (-vec3_dot(pl.normal, pl.point));
}

static int	rt_resolve_plane_hit_points(t_ray ray, t_plane pl, t_float *t)
{
	
	return (0);
}

t_hit	rt_get_plane_hit(t_ray ray, t_obj *obj)
{
	t_hit	hit;
	t_float	t;

	hit = rt_hit_default();
	if (!obj || obj->type != PLANE)
		return (hit);
	if (!rt_resolve_plane_hit_points(ray, obj->plane, &t))
		return (hit);
	hit.obj = obj;
	hit.dist = t;
	hit.color = obj->plane.color;
	// hit.pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit.dist));
	// hit.normal = vec3_subtract(hit.pos, obj->sphere.center);
	// hit.normal = vec3_scale(hit.normal, (t_float)1 / obj->sphere.radius);
	return (hit);
}