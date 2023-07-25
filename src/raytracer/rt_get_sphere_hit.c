/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_sphere_hit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 13:42:14 by dapereir         ###   ########.fr       */
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

static t_vec2	rt_get_sphere_hit_tex_coord(t_obj *obj, t_vec3 hit_normal)
{
	t_vec2	p;
	t_mat4	mr_inv;

	mr_inv = mat4_from_quat(quat_invert(obj->tf.rotate));
	hit_normal = mat4_multiply_axis(mr_inv, hit_normal);
	p.x = 0.5 + atan2(hit_normal.z, hit_normal.x) / (2.0 * M_PI);
	p.y = 0.5 - asin(hit_normal.y) / M_PI;
	return (p);
}

static t_rgb	rt_get_sphere_hit_color(t_obj *obj, t_sphere sp, \
	t_vec3 hit_normal)
{
	t_rgb	color;
	t_vec2	p;

	if (obj->tex_type == CHESS)
	{
		p = rt_get_sphere_hit_tex_coord(obj, hit_normal);
		p.x *= M_PI * sp.radius * 2;
		p.y *= M_PI * sp.radius;
		color = rt_get_chess_color(p, obj->chess);
	}
	else if (obj->tex_type == XPM)
	{
		p = rt_get_sphere_hit_tex_coord(obj, hit_normal);
		p.x *= obj->xpm.width;
		p.y *= obj->xpm.height;
		color = rt_get_tex_pixel(p, obj->xpm);
	}
	else
		color = obj->color;
	return (color);
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
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_subtract(hit->pos, sp.center);
	hit->normal = vec3_scale(hit->normal, (t_float)1 / sp.radius);
	if (vec3_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1);
	hit->color = rt_get_sphere_hit_color(obj, sp, hit->normal);
	return (1);
}
