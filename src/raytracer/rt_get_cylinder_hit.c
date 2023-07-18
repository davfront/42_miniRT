/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/18 23:28:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	rt_project_pos_on_cylinder_disc(t_cylinder cy, t_vec3 point)
{
	t_vec3	cy_center_to_point;
	t_vec3	point_on_axis;
	t_vec3	point_on_disc;

	cy_center_to_point = vec3_subtract(point, cy.center);
	point_on_axis = vec3_scale(cy.axis, vec3_dot(cy.axis, cy_center_to_point));
	point_on_disc = vec3_subtract(cy_center_to_point, point_on_axis);
	return (point_on_disc);
}

static t_vec3	rt_project_dir_on_cylinder_disc(t_cylinder cy, t_vec3 dir)
{
	t_vec3	dir_on_axis;
	t_vec3	dir_on_disc;

	dir_on_axis = vec3_scale(cy.axis, vec3_dot(cy.axis, dir));
	dir_on_disc = vec3_subtract(dir, dir_on_axis);
	return (dir_on_disc);
}

static int	rt_is_valid_cylinder_body_hit_dist(t_ray ray, t_cylinder cy, \
	t_float t_max, t_float t)
{
	t_vec3	hit_pos;
	t_float	hit_pos_on_axis;

	if (t < T_MIN || t > t_max)
		return (0);
	hit_pos = vec3_add(ray.pos, vec3_scale(ray.dir, t));
	hit_pos_on_axis = vec3_dot(vec3_subtract(hit_pos, cy.center), cy.axis);
	return (fabs(hit_pos_on_axis) * 2 < cy.height);
}

static t_float	rt_get_cylinder_body_hit_dist(t_ray ray, t_cylinder cy, \
	t_float t_max)
{
	t_ray	ray_on_disc;
	t_float	a;
	t_float	b;
	t_float	c;
	t_float	delta;

	ray_on_disc.pos = rt_project_pos_on_cylinder_disc(cy, ray.pos);
	ray_on_disc.dir = rt_project_dir_on_cylinder_disc(cy, ray.dir);
	a = vec3_length_squared(ray_on_disc.dir);
	if (sqrt(fabs(a)) < 1e-6)
		return (INFINITY);
	b = vec3_dot(ray_on_disc.dir, ray_on_disc.pos);
	c = vec3_length_squared(ray_on_disc.pos) - pow(cy.radius, 2);
	delta = pow(b, 2) - a * c;
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	if (rt_is_valid_cylinder_body_hit_dist(ray, cy, t_max, (-b - delta) / a))
		return ((-b - delta) / a);
	if (rt_is_valid_cylinder_body_hit_dist(ray, cy, t_max, (-b + delta) / a))
		return ((-b + delta) / a);
	return (INFINITY);
}

int	rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_cylinder	cy;
	t_float		t_body;
	t_vec3		hit_pos_on_disc;

	if (!obj || obj->type != CYLINDER)
		return (0);
	cy = rt_get_transformed_cylinder(*obj);
	t_body = rt_get_cylinder_body_hit_dist(ray, cy, t_max);
	if (!isfinite(t_body))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t_body;
	hit->color = cy.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit_pos_on_disc = rt_project_pos_on_cylinder_disc(cy, hit->pos);
	hit->normal = vec3_scale(hit_pos_on_disc, (t_float)1 / cy.radius);
	if (vec3_dot(ray.dir, hit->normal) > 0)
		hit->normal = vec3_scale(hit->normal, -1);
	return (1);
}
