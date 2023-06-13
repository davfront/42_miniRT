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
	t_float	d;
	t_vec3	temp;

	temp = vec3_subtract(ray.pos, pl.point);
	d = rt_find_plane_coef(pl);
	*t = - ((vec3_dot(pl.normal, temp) + d) / vec3_dot(ray.dir, pl.normal));
	if (*t < 0.0 || *t == NAN)
		return (0);
	return (*t);
}

t_hit	rt_get_plane_hit(t_ray ray, t_obj *obj)
{
	t_hit	hit;
	t_float	t;

	hit = rt_hit_default();
	if (!obj || obj->type != PLANE)
		return (hit);
	if (vec3_dot(ray.dir, obj->plane.normal) == 0.0 \
		|| !rt_resolve_plane_hit_points(ray, obj->plane, &t))
		return (hit);
	hit.obj = obj;
	hit.dist = t;
	hit.color = obj->plane.color;
	hit.pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit.dist));
	return (hit);
}