/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_hit_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 00:59:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	rt_color_reflect(t_data *data, t_hit hit, t_ray ray)
{
	t_ray	reflect_ray;
	t_rgb	reflect_color;

	if (ray.id >= RAY_DEPTH)
		return (rgb(0, 0, 0));
	reflect_ray.id = ray.id + 1;
	reflect_ray.pos = hit.pos;
	reflect_ray.dir = vec3_reflect(ray.dir, hit.normal);
	reflect_ray.hit = rt_hit_default();
	reflect_ray.hit = rt_get_closest_hit(data, reflect_ray);
	reflect_color = rt_get_hit_color(data, reflect_ray);
	return (reflect_color);
}

t_rgb	rt_get_hit_color(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_rgb	color;

	hit = ray.hit;
	color = rgb(0, 0, 0);
	if (!hit.obj || !isfinite(hit.dist))
		return (color);
	if (hit.obj->mtl.kr != 1)
		color = rt_phong_color(data, ray);
	if (hit.obj->mtl.kr != 0)
		color = rgb_mix(color, rt_color_reflect(data, hit, ray), \
			hit.obj->mtl.kr);
	return (color);
}
