/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/11 17:09:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_plane	rt_transformed_plane(t_obj obj)
{
	t_plane	pl;

	pl = obj.plane;
	pl.point = mat4_multiply_vec3(obj.mt, vec3(0, 0, 0));
	pl.normal = mat4_multiply_axis(obj.mt, vec3(0, 1, 0));
	return (pl);
}

int	rt_get_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_plane	pl;
	t_float	t;
	t_float	denum;
	t_float	num;

	if (!obj || obj->type != PLANE)
		return (0);
	pl = rt_transformed_plane(*obj);
	denum = vec3_dot(ray.dir, pl.normal);
	if (!denum)
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
	hit->color = pl.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_scale(pl.normal, 1 - 2 * (denum > 0));
	return (1);
}
