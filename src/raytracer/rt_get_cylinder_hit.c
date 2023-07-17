/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:08:06 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/17 16:18:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_quadratic_calcul(t_ray ray, t_cylinder cyl, t_vec3 *quad_va)
{
	t_vec3	AO;
	t_vec3	AOxAB;
	t_vec3	VxAB;

	// AO is vector from A to ray positi, on / origin
	AO = vec3_subtract(ray.pos, cyl.bot);
	// AOxAB cross product between AO and AB
	AOxAB = vec3_cross(AO, cyl.vec_height);
	// VxAB V is ray direction
	VxAB = vec3_cross(ray.dir, cyl.vec_height);
	// quadratic coef a, b, c
	quad_va->x = vec3_dot(VxAB, VxAB);
	quad_va->y = vec3_dot(VxAB, AOxAB) * 2;
	quad_va->z = vec3_dot(AOxAB, AOxAB) \
					- (cyl.radius * cyl.radius * cyl.vec_h_square);
	// discriminent
	return (quad_va->y * quad_va->y - 4 * quad_va->x * quad_va->z);
}

static int	rt_find_roots(t_vec3 q_val, t_float d, t_float t_max, t_float *t)
{
	t_float	temp;

	t[0] = INFINITY;
	t[1] = INFINITY;
	t[0] = (-q_val.y - sqrt(d)) / ((t_float)2 * q_val.x);
	t[1] = (-q_val.y + sqrt(d)) / ((t_float)2 * q_val.x);
	if (t[0] > t[1])
	{
		temp = t[0];
		t[0] = t[1];
		t[1] = temp;
	}
	if (isfinite(t[0]) && t[0] >= T_MIN && t[0] <= t_max)
		return (1);
	if (isfinite(t[1]) && t[1] >= T_MIN && t[1] <= t_max)
		return (1);
	return (0);
}

static void	rt_ip_calcul(t_ray ray, t_cylinder cyl, t_float *t, t_vec3 *ip)
{
	t_vec3	intersection;
	t_vec3	projection;
	t_float	proj_on_center;
	t_vec3	hit_bot;

	intersection = vec3_add(ray.pos, vec3_scale(ray.dir, t[0]));
	ip[0] = intersection;
	hit_bot = vec3_subtract(ip[0], cyl.bot);
	proj_on_center = vec3_dot(cyl.vec_height, hit_bot) / cyl.vec_h_square;
	projection = vec3_add(cyl.bot, vec3_scale(cyl.vec_height, proj_on_center));
	ip[1] = projection;
	ip[2] = vec3_subtract(intersection, projection);
}

static int	rt_is_in_cyl(t_cylinder cylinder, t_vec3 *inter_proj)
{
	t_float	top_vec_length;
	t_float	bot_vec_length;

	top_vec_length = vec3_length(vec3_subtract(inter_proj[1], cylinder.top));
	bot_vec_length = vec3_length(vec3_subtract(inter_proj[1], cylinder.bot));
	if ((bot_vec_length + top_vec_length) > vec3_length(cylinder.vec_height))
		return (0);
	return (1);
}

int	rt_get_cylinder_body_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float		t[2];
	t_float		d;
	t_vec3		quad_val;
	t_vec3		in_proj[3];
	t_cylinder	cyl;

	if (!obj || obj->type != CYLINDER)
		return (0);
	cyl = obj->cylinder;
	d = rt_quadratic_calcul(ray, cyl, &quad_val);
	if (d < 0 || !rt_find_roots(quad_val, d, t_max, t))
		return (0);
	rt_ip_calcul(ray, cyl, t, in_proj);
	if (!rt_is_in_cyl(cyl, in_proj))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t[0];
	hit->color = cyl.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_scale(in_proj[2], (t_float)1 / cyl.radius);
	return (1);
}

int	rt_get_cylinder_top_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_hit	pl_hit;
	t_obj	pl_obj;

	pl_obj.type = PLANE;
	pl_obj.plane.color = obj->cylinder.color;
	pl_obj.plane.point = vec3_add(obj->cylinder.center, vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2));
	pl_obj.plane.normal = obj->cylinder.axis;
	if (!rt_get_plane_hit(ray, &pl_obj, t_max, &pl_hit))
		return (0);
	if (vec3_length(vec3_subtract(pl_obj.plane.point, pl_hit.pos)) > obj->cylinder.radius)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = pl_hit.dist;
	hit->color = pl_hit.color;
	hit->pos = pl_hit.pos;
	hit->normal = pl_hit.normal;
	return (1);
}

int	rt_get_cylinder_bottom_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_hit	pl_hit;
	t_obj	pl_obj;

	pl_obj.type = PLANE;
	pl_obj.plane.color = obj->cylinder.color;
	pl_obj.plane.point = vec3_subtract(obj->cylinder.center, vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2));
	pl_obj.plane.normal = vec3_scale(obj->cylinder.axis, -1);
	if (!rt_get_plane_hit(ray, &pl_obj, t_max, &pl_hit))
		return (0);
	if (vec3_length(vec3_subtract(pl_obj.plane.point, pl_hit.pos)) > obj->cylinder.radius)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = pl_hit.dist;
	hit->color = pl_hit.color;
	hit->pos = pl_hit.pos;
	hit->normal = pl_hit.normal;
	return (1);
}

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	int		res[3];
	t_hit	subpart_hit[3];
	t_hit	cy_hit;

	if (!obj || obj->type != CYLINDER)
		return (0);
	res[0] = rt_get_cylinder_body_hit(ray, obj, t_max, subpart_hit);
	res[1] = rt_get_cylinder_top_hit(ray, obj, t_max, subpart_hit + 1);
	res[2] = rt_get_cylinder_bottom_hit(ray, obj, t_max, subpart_hit + 2);
	if (!hit)
		return (res[0] || res[1] || res[2]);
	cy_hit = rt_hit_default();
	if (res[0])
		cy_hit = subpart_hit[0];
	if (res[1] && subpart_hit[1].dist < cy_hit.dist)
		cy_hit = subpart_hit[1];
	if (res[2] && subpart_hit[2].dist < cy_hit.dist)
		cy_hit = subpart_hit[2];
	if (res[0] || res[1] || res[2])
		*hit = cy_hit;
	return (res[0] || res[1] || res[2]);
}