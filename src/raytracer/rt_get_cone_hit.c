/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cone_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 13:50:47 by dapereir         ###   ########.fr       */
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
		angle = atan(co.radius / co.height);
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
	hit->color = obj->cone.color;
	hit->dist = t_min;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = rt_get_cone_hit_normal(ray, co, hit->pos, t_min == t[0]);
	return (1);
}
