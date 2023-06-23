/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/23 19:04:39 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float	t;
    t_vec3	A, B;
	t_vec3	AB, AO, AOxAB, VxAB;
	t_float	ab2, a, b, c, d;
	t_vec3	intersection, projection;
	t_vec3	displacement;
	// t_hit	hit_a;
	// t_hit	hit_b;
	t_obj	ob_p;
	int	val;

	ob_p.type = PLANE;
	if (!obj || obj->type != CYLINDER)
		return (0);
	displacement = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2);
	A = vec3_subtract(obj->cylinder.center, displacement);
	ob_p.plane.point = A;
	ob_p.plane.normal = obj->cylinder.axis;
	ob_p.plane.color = obj->cylinder.color;
	B = vec3_add(obj->cylinder.center, displacement);
	// ob_p.plane.point = B;
	// ob_p.plane.normal = obj->cylinder.axis;
	// ob_p.plane.color = obj->cylinder.color;
	val = rt_get_plane_hit(ray, &ob_p, t_max, hit);
	if (val && vec3_length(vec3_subtract(hit->pos, A)) <= obj->cylinder.radius)
		return (1);
	else
	{
		if (!hit)
			return (1);
		*hit = rt_hit_default();
		return (0);
	}
	// rt_get_plane_hit(ray, &ob_p, t_max, &hit_b);
	// if (hit_a.dist > hit_b.dist)
	// 	hit_a.dist = hit_b.dist;
	AB = vec3_subtract(B, A);
	AO = vec3_subtract(ray.pos, A);
	AOxAB = vec3_cross(AO, AB);
	VxAB = vec3_cross(ray.dir, AB);
	ab2 = vec3_dot(AB, AB);
	a = vec3_dot(VxAB, VxAB);
	b = vec3_dot(VxAB, AOxAB) * 2;
	c = vec3_dot(AOxAB, AOxAB) - (obj->cylinder.radius * obj->cylinder.radius * ab2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (0);
	t = (-b - sqrt(d)) / (2 * a);
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (0);
	intersection = vec3_add(ray.pos, vec3_scale(ray.dir, t));
	projection = vec3_add(A, vec3_scale(AB, vec3_dot(AB, vec3_subtract(intersection, A)) / ab2)); 
	if ((vec3_length(vec3_subtract(projection, A)) +\
	 vec3_length(vec3_subtract(projection, B))) > vec3_length(AB))
	 	return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t;
	hit->color = obj->cylinder.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_subtract(intersection, projection);
	return (1);
}
