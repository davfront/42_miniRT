/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_sphere_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 20:01:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_sphere	rt_transformed_sphere(t_obj obj)
{
	t_sphere	sp;

	sp = obj.sphere;
	sp.center = mat4_multiply_vec3(obj.mt, vec3(0, 0, 0));
	sp.radius = vec3_length(\
		vec3_subtract(mat4_multiply_vec3(obj.mt, vec3(1, 0, 0)), sp.center));
	return (sp);
}

static int	rt_resolve_sphere_hit_points(t_ray ray, t_sphere sp, t_float t[2], \
	int *front_face)
{
	t_vec3	ray_pos_sp;
	t_float	b;
	t_float	c;
	t_float	delta;

	if (!t || !front_face)
		return (0);
	ray_pos_sp = vec3_subtract(ray.pos, sp.center);
	b = vec3_dot(ray_pos_sp, ray.dir);
	c = vec3_length_squared(ray_pos_sp) - pow(sp.radius, 2);
	delta = -c + pow(b, 2);
	if (delta < 0)
		return (0);
	delta = sqrt(delta);
	t[0] = -b - delta;
	t[1] = -b + delta;
	*front_face = (c > 0);
	return (1);
}

int	rt_get_sphere_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_sphere	sp;
	t_float		t[2];
	t_float		hit_dist;
	int			front_face;

	if (!obj || obj->type != SPHERE)
		return (0);
	sp = rt_transformed_sphere(*obj);
	if (!rt_resolve_sphere_hit_points(ray, sp, t, &front_face))
		return (0);
	hit_dist = t[0];
	if (hit_dist < T_MIN || hit_dist > t_max)
		hit_dist = t[1];
	if (hit_dist < T_MIN || hit_dist > t_max)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = hit_dist;
	hit->color = sp.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_subtract(hit->pos, sp.center);
	hit->normal = vec3_scale(hit->normal, (2.0 * front_face - 1) / sp.radius);
	return (1);
}
