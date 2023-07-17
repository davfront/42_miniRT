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
	t[0] = INFINITY;
	t[1] = INFINITY;
	t[0] = (-q_val.y - sqrt(d)) / (2 * q_val.x);
	t[1] = (-q_val.y + sqrt(d)) / (2 * q_val.x);
	if (t[0] > t[1])
		t[0] = t[1];
	if (!isfinite(t[0]) || t[0] < T_MIN || t[0] > t_max)
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
	t_float	top_vec_lenght;
	t_float	bot_vec_lenght;

	top_vec_lenght = vec3_length(vec3_subtract(inter_proj[1], cylinder.top));
	bot_vec_lenght = vec3_length(vec3_subtract(inter_proj[1], cylinder.bot));
	if ((bot_vec_lenght + top_vec_lenght) > vec3_length(cylinder.vec_height))
		return (0);
	return (1);
}

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
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
	if (d < 0 || rt_find_roots(quad_val, d, t_max, t))
		return (0);
	rt_ip_calcul(ray, cyl, t, in_proj);
	if (!rt_is_in_cyl(cyl, in_proj))
		t[0] = INFINITY;
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t[0];
	hit->color = cyl.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_scale(in_proj[2], 1 / cyl.radius);
	return (1);
}
