/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_sphere_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 00:06:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_get_sphere_hit_dist(t_ray ray, t_sphere sp, t_float t_max)
{
	t_vec3	ray_pos_sp;
	t_float	b;
	t_float	c;
	t_float	delta;
	t_float	t;

	ray_pos_sp = vec3_subtract(ray.pos, sp.center);
	b = vec3_dot(ray_pos_sp, ray.dir);
	c = vec3_length_squared(ray_pos_sp) - pow(sp.radius, 2);
	delta = -c + pow(b, 2);
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	t = -b - delta;
	if (t >= T_MIN && t <= t_max)
		return (t);
	t = -b + delta;
	if (t >= T_MIN && t <= t_max)
		return (t);
	return (INFINITY);
}

int	rt_get_sphere_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_sphere	sp;
	t_float		hit_dist;

	if (!obj || obj->type != SPHERE)
		return (0);
	sp = rt_get_transformed_sphere(*obj);
	hit_dist = rt_get_sphere_hit_dist(ray, sp, t_max);
	if (!isfinite(hit_dist))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = hit_dist;
	hit->color = sp.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_subtract(hit->pos, sp.center);
	hit->normal = vec3_scale(hit->normal, (t_float)1 / sp.radius);
	if (vec3_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1);
	return (1);
}
