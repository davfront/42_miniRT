/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/26 19:57:11 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	int	rt_cyl_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float	t;
	t_float	denum;
	t_float	num;
	t_plane	plane;

	if (!obj || obj->type != PLANE)
		return (0);
	plane = obj->plane;
	denum = vec3_dot(ray.dir, plane.normal);
	if (!denum)
		return (0);
	num = vec3_dot(vec3_subtract(plane.point, ray.pos), plane.normal);
	t = num / denum;
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t;
	hit->color = plane.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_scale(plane.normal, 1 - 2 * (denum > 0));
	return (1);
}

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

// static void	rt_get_top_and_bot(t_vec3 *top, t_vec3 *bot, t_obj *obj)
// {
// 	t_vec3	dis;

// 	dis = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2);
// 	*top = vec3_add(obj->cylinder.center, dis);
// 	*bot = vec3_subtract(obj->cylinder.center, dis);
// }

// // TODO change this
// static t_vec3	pre_compute_coef(t_vec3 v1, t_vec3 v2)
// {
// 	return (vec3_subtract(v1, vec3_scale(v2, vec3_dot(v1, v2))));
// }

// int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
// {
// 	t_vec3	top, bot;
// 	t_vec3	quad;
// 	t_vec3	oc, dir, ocdir;

// 	rt_get_top_and_bot(&top, &bot, obj);
// 	oc = vec3_subtract(ray.pos, bot);
// 	dir = pre_compute_coef(ray.dir, obj->cylinder.axis);
// 	ocdir = pre_compute_coef(oc, obj->cylinder.axis);
// 	quad = 
// }

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float	t, tp;
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
	
	ob_pa.type = PLANE;
	ob_pb.type = PLANE;
	if (!obj || obj->type != CYLINDER)
		return (0);
	displacement = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2);
	A = vec3_subtract(obj->cylinder.center, displacement);
	ob_pa.plane.point = A;
	ob_pa.plane.normal = obj->cylinder.axis;
	ob_pa.plane.color = obj->cylinder.color;
	vala = rt_cyl_plane_hit(ray, &ob_pa, t_max, &hit_a);
	B = vec3_add(obj->cylinder.center, displacement);
	ob_pb.plane.point = B;
	ob_pb.plane.normal = obj->cylinder.axis;
	ob_pb.plane.color = obj->cylinder.color;
	valb = rt_cyl_plane_hit(ray, &ob_pb, t_max, &hit_b);
	// if (vala && vec3_length(vec3_subtract(hit->pos, A)) <= obj->cylinder.radius)
	// 	return (1);
	// else
	// {
	// 	if (!hit)
	// 		return (1);
	// 	*hit = rt_hit_default();
	// 	return (0);
	// }
	if (valb && !(vec3_length(vec3_subtract(hit_a.pos, B)) <= obj->cylinder.radius))
		valb = 0;
	if (vala && !(vec3_length(vec3_subtract(hit_b.pos, A)) <= obj->cylinder.radius))
		vala = 0;
	tp = nearest_dist(hit_a, hit_b, vala, valb);
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
	if (tp < ((-b + sqrt(d)) / (2 * a)))
		t_e = 1;
	if (t_e)
	{
		if (hit_a.dist > hit_b.dist)
			rt_cyl_plane_hit(ray, &ob_pb, t_max, hit);
		else 
			rt_cyl_plane_hit(ray, &ob_pa, t_max, hit);
		// if (!rt_cyl_plane_hit(ray, &ob_pa, t_max, hit))
		// 	rt_cyl_plane_hit(ray, &ob_pb, t_max, hit);
	}
	else
	{
		*hit = rt_hit_default();
		hit->obj = obj;
		hit->dist = t;
		hit->color = obj->cylinder.color;
		hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
		hit->normal = vec3_subtract(intersection, projection);	
	}
	return (1);
}
