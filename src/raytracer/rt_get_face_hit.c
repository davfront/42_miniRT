/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_face_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/16 23:06:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_get_face_hit(t_ray ray, t_obj *obj)
{	t_hit	hit;
	t_float	t;

	hit = rt_hit_default();
	if (!obj || obj->type != FACE)
		return (hit);
	t_vec3	h = vec3_cross(ray.dir, obj->face.edge2);
	t_float	det = vec3_dot(obj->face.edge1, h);
	if (fabs(det) < 1e-6)
		return (hit);
	t_vec3	s = vec3_subtract(ray.pos, *obj->face.v[0]);
	t_float u = vec3_dot(s, h) / det;
	t_float v = vec3_dot(ray.dir, vec3_cross(s, obj->face.edge1)) / det;
	if ( u < 0 || v < 0 || (u + v) > 1)
		return (hit);
	t = vec3_dot(obj->face.edge2, vec3_cross(s, obj->face.edge1)) / det;
	if (t < NEAR || t > FAR)
		return (hit);
	hit.obj = obj;
	hit.dist = t;
	hit.color = rgb(255, 255, 255);
	hit.pos = vec3_add(ray.pos, vec3_scale(ray.dir, t));
	hit.normal = vec3_scale(obj->face.normal, 1 - 2 * (det < 0));
	return (hit);
}
