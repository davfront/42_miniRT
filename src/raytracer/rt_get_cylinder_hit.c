/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/28 18:24:56 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	nearest_dist(t_hit a, t_hit b, int vala, int valb)
{
	if (!vala && !valb)
		return (INFINITY);
	if (!vala)
		return (b.dist);
	if (!valb)
		return (a.dist);
	if (a.dist > b.dist)
		return (b.dist);
	else
		return (a.dist);
}

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float	t1, t2, tp;
	t_vec3	A, B;
	t_vec3	AB, AO, AOxAB, VxAB;
	t_float	ab2, a, b, c, d;
	t_vec3	intersection, projection;
	t_vec3	displacement;
	t_hit	hit_a;
	t_hit	hit_b;
	t_obj	ob_pa;
	t_obj	ob_pb;
	int		vala;
	int		valb;
	int		t_e = 0;
	
	// create top and bot plane
	ob_pa.type = PLANE;
	ob_pb.type = PLANE;
	if (!obj || obj->type != CYLINDER)
		return (0);
	// distance from center to one side
	displacement = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2);
	// A is bottom point center
	A = vec3_subtract(obj->cylinder.center, displacement);
	ob_pa.plane.point = A;
	ob_pa.plane.normal = obj->cylinder.axis;
	ob_pa.plane.color = obj->cylinder.color;
	// getting hit point of bottom plane in hit_a
	vala = rt_get_plane_hit(ray, &ob_pa, t_max, &hit_a);
	// B is top point center
	B = vec3_add(obj->cylinder.center, displacement);
	ob_pb.plane.point = B;
	ob_pb.plane.normal = obj->cylinder.axis;
	ob_pb.plane.color = obj->cylinder.color;
	// getting hit point of bottom plane in hit_b
	valb = rt_get_plane_hit(ray, &ob_pb, t_max, &hit_b);
	// Check if the hitting point is inside the circle
	if (valb && !(vec3_length(vec3_subtract(hit_a.pos, B)) <= obj->cylinder.radius))
		valb = 0;
	if (vala && !(vec3_length(vec3_subtract(hit_b.pos, A)) <= obj->cylinder.radius))
		vala = 0;
	// get the nearest hit point
	tp = nearest_dist(hit_a, hit_b, vala, valb);
	// AB is vector from bot to top
	AB = vec3_subtract(B, A);
	// AO is vector from A to ray position / origin
	AO = vec3_subtract(ray.pos, A);
	// AOxAB cross product between AO and AB
	AOxAB = vec3_cross(AO, AB);
	// VxAB V is ray direction
	VxAB = vec3_cross(ray.dir, AB);
	ab2 = vec3_dot(AB, AB);
	// quadratic coef a, b, c
	a = vec3_dot(VxAB, VxAB);
	b = vec3_dot(VxAB, AOxAB) * 2;
	c = vec3_dot(AOxAB, AOxAB) - (obj->cylinder.radius * obj->cylinder.radius * ab2);
	// discriminent
	d = b * b - 4 * a * c;
	t1 = INFINITY;
	t2 = INFINITY;
	// getting roots t1 and t2
	if (d >= 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		t2 = (-b + sqrt(d)) / (2 * a);
		if (t1 > t2)
			t1 = t2;
		if (!isfinite(t1) || t1 < T_MIN || t1 > t_max)
			return (0);
		intersection = vec3_add(ray.pos, vec3_scale(ray.dir, t1));
		projection = vec3_add(A, vec3_scale(AB, vec3_dot(AB, vec3_subtract(intersection, A)) / ab2)); 
		if ((vec3_length(vec3_subtract(projection, A)) +\
		vec3_length(vec3_subtract(projection, B))) > vec3_length(AB))
			t1 = INFINITY;
	}
	if (!hit)
		return (1);
	// choosing between plane or cylinder
	if (tp <= t1)
		t_e = 1;
	if (t_e)
	{
		if (hit_a.dist > hit_b.dist)
		{
			*hit = hit_b;
			if (vec3_length(vec3_subtract(hit->pos, B)) > obj->cylinder.radius)
			{
				*hit = rt_hit_default();
				return (0);
			}
		}
		else
		{
			*hit = hit_a;
			if (vec3_length(vec3_subtract(hit->pos, A)) > obj->cylinder.radius)
			{
				*hit = rt_hit_default();
				return (0);
			}
		}
	}
	else
	{
		*hit = rt_hit_default();
		hit->obj = obj;
		hit->dist = t1;
		hit->color = obj->cylinder.color;
		hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
		hit->normal = vec3_scale(vec3_subtract(intersection, projection), 1 / obj->cylinder.radius);	
	}
	return (1);
}
