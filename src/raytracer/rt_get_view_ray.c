/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_view_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/11 10:42:23 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	rt_ray_dir_right_offset(t_cam cam, int x)
{
	t_float	ndc_x;
	t_vec3	right_offset;

	ndc_x = (2.0 / WIN_WIDTH * (x + 0.5)) - 1.0;
	right_offset = vec3_scale(cam.right, \
		ndc_x * cam.aspect_ratio * tan(cam.fov / 2));
	return (right_offset);
}

static t_vec3	rt_ray_dir_top_offset(t_cam cam, int y)
{
	t_float	ndc_y;
	t_vec3	top_offset;

	ndc_y = 1.0 - (2.0 / WIN_HEIGHT * (y + 0.5));
	top_offset = vec3_scale(cam.top, ndc_y * tan(cam.fov / 2));
	return (top_offset);
}

t_ray	rt_get_view_ray(t_cam cam, int x, int y)
{
	t_ray	ray;

	ray.pos = cam.pos;
	ray.dir = cam.dir;
	ray.dir = vec3_add(ray.dir, rt_ray_dir_right_offset(cam, x));
	ray.dir = vec3_add(ray.dir, rt_ray_dir_top_offset(cam, y));
	ray.dir = vec3_normalize(ray.dir);
	return (ray);
}
