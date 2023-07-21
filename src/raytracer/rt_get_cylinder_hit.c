/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cylinder_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/21 01:20:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_float	rt_get_cylinder_disc_hit_dist(t_ray ray, t_cylinder cy, \
	t_float t_max, int is_top)
{
	t_disc3	disc;

	if (is_top)
		disc.center = vec3_add(cy.center, vec3_scale(cy.axis, cy.height / 2));
	else
		disc.center = vec3_add(cy.center, vec3_scale(cy.axis, -cy.height / 2));
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

static t_vec2	rt_get_cylinder_hit_tex_coord(t_obj *obj, t_cylinder cy, \
	t_vec3 hit_pos, int is_body)
{
	t_vec3	cy_center_to_pos;
	t_mat4	mr;
	t_vec3	v[2];
	t_vec2	p;

	cy_center_to_pos = vec3_subtract(hit_pos, cy.center);
	mr = mat4_from_quat(obj->tf.rotate);
	v[0] = mat4_multiply_axis(mr, vec3(1, 0, 0));
	v[1] = mat4_multiply_axis(mr, vec3(0, 0, -1));
	if (is_body)
	{
		p.x = vec3_dot(cy.axis, cy_center_to_pos);
		p.y = cy.radius * atan(vec3_dot(cy_center_to_pos, v[1]) / \
			vec3_dot(cy_center_to_pos, v[0]));
	}
	else
	{
		p.x = vec3_dot(cy_center_to_pos, v[0]);
		p.y = vec3_dot(cy_center_to_pos, v[1]);
	}
	return (p);
}

static t_rgb	rt_get_cylinder_hit_color(t_obj *obj, t_cylinder cy, \
	t_vec3 hit_pos, int is_body)
{
	t_rgb	color;
	t_vec2	p;

	if (obj->tex_type == CHESS)
	{
		p = rt_get_cylinder_hit_tex_coord(obj, cy, hit_pos, is_body);
		color = rt_get_chess_color(p, obj->chess);
	}
	else
		color = obj->color;
	return (color);
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
	t[1] = rt_get_cylinder_disc_hit_dist(ray, cy, t_max, 1);
	t[2] = rt_get_cylinder_disc_hit_dist(ray, cy, t_max, 0);
	t_min = fmin(t[0], fmin(t[1], t[2]));
	if (!isfinite(t_min))
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t_min;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = rt_get_cylinder_hit_normal(ray, cy, hit->pos, t_min == t[0]);
	hit->color = rt_get_cylinder_hit_color(obj, cy, hit->pos, t_min == t[0]);
	return (1);
}
