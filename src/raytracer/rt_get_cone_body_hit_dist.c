/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_cone_body_hit_dist.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 13:15:29 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	rt_project_pos_on_cone_plane(t_cone co, t_vec3 point)
{
	t_vec3	co_center_to_point;
	t_vec3	point_on_axis;
	t_vec3	point_on_plane;

	co_center_to_point = vec3_subtract(point, co.center);
	point_on_axis = vec3_scale(co.axis, vec3_dot(co.axis, co_center_to_point));
	point_on_plane = vec3_subtract(co_center_to_point, point_on_axis);
	return (point_on_plane);
}

static t_vec3	rt_project_dir_on_cone_plane(t_cone co, t_vec3 dir)
{
	t_vec3	dir_on_axis;
	t_vec3	dir_on_plane;

	dir_on_axis = vec3_scale(co.axis, vec3_dot(co.axis, dir));
	dir_on_plane = vec3_subtract(dir, dir_on_axis);
	return (dir_on_plane);
}

static int	rt_is_valid_cone_body_hit_dist(t_ray ray, t_cone co, \
	t_float t_max, t_float t)
{
	t_vec3	hit_pos;
	t_float	hit_pos_on_axis;

	if (t < T_MIN || t > t_max)
		return (0);
	hit_pos = vec3_add(ray.pos, vec3_scale(ray.dir, t));
	hit_pos_on_axis = vec3_dot(vec3_subtract(hit_pos, co.center), co.axis);
	return (hit_pos_on_axis >= 0 && hit_pos_on_axis <= co.height);
}

static void	rt_get_cone_body_hit_dist_parameters(t_ray ray, t_cone co, \
	t_vec3 v[2], t_float f[3])
{
	if (!v || !f)
		return ;
	v[0] = rt_project_pos_on_cone_plane(co, ray.pos);
	v[1] = rt_project_dir_on_cone_plane(co, ray.dir);
	f[0] = vec3_dot(ray.dir, co.axis);
	f[1] = co.height - vec3_dot(vec3_subtract(ray.pos, co.center), co.axis);
	f[2] = co.radius / co.height;
}

t_float	rt_get_cone_body_hit_dist(t_ray ray, t_cone co, t_float t_max)
{
	t_vec3	v[2];
	t_float	f[3];
	t_float	a[3];
	t_float	t;
	t_float	delta;

	rt_get_cone_body_hit_dist_parameters(ray, co, v, f);
	a[0] = vec3_length_squared(v[1]) - pow(f[0] * f[2], 2);
	a[1] = 2.0 * vec3_dot(v[1], v[0]) + 2 * f[1] * f[0] * pow(f[2], 2);
	a[2] = vec3_length_squared(v[0]) - pow(f[1] * f[2], 2);
	delta = a[1] * a[1] - 4 * a[0] * a[2];
	if (delta < 0)
		return (INFINITY);
	delta = sqrt(delta);
	t = (-a[1] - delta) / (2 * a[0]);
	if (rt_is_valid_cone_body_hit_dist(ray, co, t_max, t))
		return (t);
	t = (-a[1] + delta) / (2 * a[0]);
	if (rt_is_valid_cone_body_hit_dist(ray, co, t_max, t))
		return (t);
	return (INFINITY);
}
