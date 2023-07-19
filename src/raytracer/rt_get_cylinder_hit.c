/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 12:39:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_get_cylinder_top_hit_dist(t_ray ray, t_cylinder cy, \
	t_float t_max)
{
	t_disc3	disc;

	disc.center = vec3_add(cy.center, vec3_scale(cy.axis, cy.height / 2));
	disc.axis = cy.axis;
	disc.radius = cy.radius;
	return (rt_get_disc_hit_dist(ray, disc, t_max));
}

static t_float	rt_get_cylinder_bottom_hit_dist(t_ray ray, t_cylinder cy, \
	t_float t_max)
{
	t_disc3	disc;

	disc.center = vec3_subtract(cy.center, vec3_scale(cy.axis, cy.height / 2));
	disc.axis = cy.axis;
	disc.radius = cy.radius;
	return (rt_get_disc_hit_dist(ray, disc, t_max));
}

static t_vec3	rt_get_cylinder_hit_normal(t_ray ray, t_cylinder cy, \
	t_vec3 hit_pos, int is_body)
{
	t_vec3	cy_center_to_pos;
	t_vec3	pos_on_axis;
	t_vec3	pos_on_disc;
	t_vec3	normal;

	if (is_body)
	{
		cy_center_to_pos = vec3_subtract(hit_pos, cy.center);
		pos_on_axis = vec3_scale(cy.axis, vec3_dot(cy.axis, cy_center_to_pos));
		pos_on_disc = vec3_subtract(cy_center_to_pos, pos_on_axis);
		normal = vec3_scale(pos_on_disc, (t_float)1 / cy.radius);
	}
	else
		normal = cy.axis;
	if (vec3_dot(ray.dir, normal) > 0)
		normal = vec3_scale(normal, -1);
	return (normal);
}

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_cylinder	cy;
	t_float		t[3];
	t_float		t_min;

	if (!obj || obj->type != CYLINDER)
		return (0);
	cy = rt_get_transformed_cylinder(*obj);
	t[0] = rt_get_cylinder_body_hit_dist(ray, cy, t_max);
	t[1] = rt_get_cylinder_top_hit_dist(ray, cy, t_max);
	t[2] = rt_get_cylinder_bottom_hit_dist(ray, cy, t_max);
	t_min = fmin(t[0], fmin(t[1], t[2]));
	if (!isfinite(t_min))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->color = obj->cylinder.color;
	hit->dist = t_min;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = rt_get_cylinder_hit_normal(ray, cy, hit->pos, t_min == t[0]);
	return (1);
}
