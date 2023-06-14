/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/12 18:45:21 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_get_plane_hit(t_ray ray, t_obj *obj)
{
	t_hit	hit;
	t_float	t;
	t_float	denum;
	t_float	num;
	t_plane	plane;

	plane = obj->plane;
	denum = vec3_dot(ray.dir, plane.normal);
	if (!denum)
		return (hit);
	num = vec3_dot(vec3_subtract(plane.point, ray.pos), plane.normal);
	hit = rt_hit_default();
	if (!obj || obj->type != PLANE)
		return (hit);
	t = num / denum;
	if (!isfinite(t) || t <= 0)
		return (hit);
	hit.obj = obj;
	hit.dist = t;
	hit.color = plane.color;
	hit.pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit.dist));
	hit.normal = vec3_scale(plane.normal, 1 - 2 * (denum < 0));
	return (hit);
}
