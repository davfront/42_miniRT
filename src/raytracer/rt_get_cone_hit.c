/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cone_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 14:07:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_get_cone_disc_hit_dist(t_ray ray, t_cone co, t_float t_max)
{
	t_disc3	disc;

	disc.center = co.center;
	disc.axis = co.axis;
	disc.radius = co.radius;
	return (rt_get_disc_hit_dist(ray, disc, t_max));
}

static t_vec3	rt_get_cone_hit_normal(t_ray ray, t_cone co, \
	t_vec3 hit_pos, int is_body)
{
	t_vec3	co_center_to_pos;
	t_vec3	pos_on_axis;
	t_vec3	pos_on_plane;
	t_float	angle;
	t_vec3	normal;

	if (is_body)
	{
		co_center_to_pos = vec3_subtract(hit_pos, co.center);
		pos_on_axis = vec3_scale(co.axis, vec3_dot(co.axis, co_center_to_pos));
		pos_on_plane = vec3_subtract(co_center_to_pos, pos_on_axis);
		angle = atan2(co.radius, co.height);
		normal = vec3_add(\
					vec3_scale(vec3_normalize(pos_on_plane), cos(angle)), \
					vec3_scale(co.axis, sin(angle)));
	}
	else
		normal = co.axis;
	if (vec3_dot(ray.dir, normal) > 0)
		normal = vec3_scale(normal, -1);
	return (normal);
}

static t_vec2	rt_get_cone_hit_tex_coord(t_obj *obj, t_cone co, \
	t_vec3 hit_pos, int is_body)
{
	t_vec3	co_center_to_pos;
	t_mat4	mr;
	t_vec3	v[2];
	t_vec2	p;

	co_center_to_pos = vec3_subtract(hit_pos, co.center);
	mr = mat4_from_quat(obj->tf.rotate);
	v[0] = mat4_multiply_axis(mr, vec3(0, 0, 1));
	v[1] = mat4_multiply_axis(mr, vec3(-1, 0, 0));
	if (is_body)
	{
		p.x = atan2(vec3_dot(co_center_to_pos, v[1]), \
			vec3_dot(co_center_to_pos, v[0])) / (2.0 * M_PI);
		p.y = 1 - vec3_dot(co.axis, co_center_to_pos) / co.height;
	}
	else
	{
		p.x = 0.5 + vec3_dot(co_center_to_pos, v[0]) / (2.0 * co.radius);
		p.y = 0.5 - vec3_dot(co_center_to_pos, v[1]) / (2.0 * co.radius);
	}
	return (p);
}

static t_rgb	rt_get_cone_hit_color(t_obj *obj, t_cone co, t_vec3 hit_pos, \
	int is_body)
{
	t_vec2	p;

	if (obj->tex_type == CHESS)
	{
		p = rt_get_cone_hit_tex_coord(obj, co, hit_pos, is_body);
		if (is_body)
		{
			p.x = p.x * 2 * M_PI * co.radius;
			p.y = p.y * co.height / cos(atan2(co.radius, co.height));
		}
		else
		{
			p.x = p.x * 2 * co.radius;
			p.y = p.y * 2 * co.radius;
		}
		return (rt_get_chess_color(p, obj->chess));
	}
	if (obj->tex_type == XPM)
	{
		p = rt_get_cone_hit_tex_coord(obj, co, hit_pos, is_body);
		p.x *= obj->xpm.width;
		p.y *= obj->xpm.height;
		return (rt_get_tex_pixel(p, obj->xpm));
	}
	return (obj->color);
}

int	rt_get_cone_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_cone	co;
	t_float	t[2];
	t_float	t_min;

	if (!obj || obj->type != CONE)
		return (0);
	co = rt_get_transformed_cone(*obj);
	t[0] = rt_get_cone_body_hit_dist(ray, co, t_max);
	t[1] = rt_get_cone_disc_hit_dist(ray, co, t_max);
	t_min = fmin(t[0], t[1]);
	if (!isfinite(t_min))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t_min;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = rt_get_cone_hit_normal(ray, co, hit->pos, t_min == t[0]);
	hit->color = rt_get_cone_hit_color(obj, co, hit->pos, t_min == t[0]);
	return (1);
}
