/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/25 01:20:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec2	rt_get_plane_hit_tex_coord(t_obj *obj, t_plane pl, \
	t_vec3 hit_pos)
{
	t_vec2	p;
	t_vec3	hit_pos_in_pl;
	t_mat4	mr;
	t_vec3	vx;
	t_vec3	vy;

	hit_pos_in_pl = vec3_subtract(hit_pos, pl.point);
	mr = mat4_from_quat(obj->tf.rotate);
	vx = mat4_multiply_axis(mr, vec3(0, 0, 1));
	vy = mat4_multiply_axis(mr, vec3(-1, 0, 0));
	p.x = vec3_dot(hit_pos_in_pl, vx);
	p.y = vec3_dot(hit_pos_in_pl, vy);
	return (p);
}

static t_rgb	rt_get_plane_hit_color(t_obj *obj, t_plane pl, t_vec3 hit_pos)
{
	t_rgb	color;
	t_vec2	p;

	if (obj->tex_type == CHESS)
		color = rt_get_chess_color(\
			rt_get_plane_hit_tex_coord(obj, pl, hit_pos), obj->chess);
	else if (obj->tex_type == XPM)
	{
		p = rt_get_plane_hit_tex_coord(obj, pl, hit_pos);
		color = rt_get_tex_pixel(p, obj->xpm);
	}
	else
		color = obj->color;
	return (color);
}

int	rt_get_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_plane	pl;
	t_float	t;
	t_float	denum;
	t_float	num;

	if (!obj || obj->type != PLANE)
		return (0);
	pl = rt_get_transformed_plane(*obj);
	denum = vec3_dot(ray.dir, pl.normal);
	if (fabs(denum) < 1e-6)
		return (0);
	num = vec3_dot(vec3_subtract(pl.point, ray.pos), pl.normal);
	t = num / denum;
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_scale(pl.normal, 1 - 2 * (denum > 0));
	hit->color = rt_get_plane_hit_color(obj, pl, hit->pos);
	return (1);
}
