/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_sphere_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/17 17:05:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_resolve_sphere_hit_points(t_ray ray, t_sphere sp)
{
	t_float	t[2];
	t_vec3	ray_pos_sp;
	t_float	b;
	t_float	c;
	t_float	delta;

	ray_pos_sp = vec3_subtract(ray.pos, sp.center);
	b = vec3_dot(ray_pos_sp, ray.dir);
	c = vec3_length_squared(ray_pos_sp) - pow(sp.radius, 2);
	delta = -c + pow(b, 2);
	if (delta < 0)
		return (INFINITY);
	if (delta != 0)
		delta = (t_float)sqrt(delta);
	t[0] = -b - delta;
	t[1] = -b + delta;
	if (t[1] < 0)
		return (INFINITY);
	if (t[0] < 0)
		return (t[1]);
	return (t[0]);
}

t_hit	rt_get_sphere_hit(t_ray ray, t_obj *obj)
{
	t_hit	hit;
	t_float	t;

	hit = rt_hit_default();
	if (!obj || obj->type != SPHERE)
		return (hit);
	t = rt_resolve_sphere_hit_points(ray, obj->sphere);
	if (t < NEAR || t > FAR)
		return (hit);
	hit.obj = obj;
	hit.dist = t;
	hit.color = obj->sphere.color;
	hit.pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit.dist));
	hit.normal = vec3_subtract(hit.pos, obj->sphere.center);
	hit.normal = vec3_scale(hit.normal, (t_float)1 / obj->sphere.radius);
	return (hit);
}
