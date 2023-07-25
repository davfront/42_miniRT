/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_phong_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/24 23:08:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_is_light_visible(t_hit hit, t_vec3 target, t_vec3 dir, \
	t_data *data)
{
	t_ray	ray;
	t_float	dist_max;
	t_list	*obj_node;

	if (vec3_dot(dir, hit.normal) < 0)
		return (0);
	ray.pos = hit.pos;
	ray.dir = dir;
	dist_max = vec3_length(vec3_subtract(target, hit.pos));
	obj_node = data->obj_lst;
	while (obj_node)
	{
		if (rt_get_obj_hit(ray, obj_node->content, dist_max, NULL))
			return (0);
		obj_node = obj_node->next;
	}
	return (1);
}

static t_rgb	rt_color_diffuse(t_hit hit, t_light light, \
	t_vec3 to_light)
{
	t_float	diffuse_factor;
	t_rgb	diffuse_color;

	diffuse_factor = fmax(vec3_dot(hit.normal, to_light), 0);
	diffuse_factor = fmax(diffuse_factor, 0.0);
	diffuse_color = rgb_multiply(hit.color, light.color);
	diffuse_color = rgb_scale(diffuse_color, light.ratio * diffuse_factor);
	return (rgb_scale(diffuse_color, hit.obj->mtl.kd));
}

static t_rgb	rt_color_specular(t_hit hit, t_light light, \
	t_vec3 to_light, t_vec3 ray_dir)
{
	t_vec3	reflect_dir;
	t_float	specular_ratio;
	t_rgb	specular_color;

	reflect_dir = vec3_reflect(to_light, hit.normal);
	specular_ratio = fmax(vec3_dot(reflect_dir, ray_dir), 0);
	specular_ratio = pow(specular_ratio, hit.obj->mtl.ns);
	specular_color = rgb_scale(light.color, light.ratio * specular_ratio);
	return (rgb_scale(specular_color, hit.obj->mtl.ks));
}

t_rgb	rt_phong_color(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_rgb	color;
	t_list	*light_node;
	t_light	*light;
	t_vec3	to_light;

	hit = ray.hit;
	if (!hit.obj || !isfinite(hit.dist))
		return (rgb(0, 0, 0));
	color = rgb_multiply(hit.color, \
		rgb_scale(data->al->computed, hit.obj->mtl.ka));
	light_node = data->light_lst;
	while (light_node)
	{
		light = light_node->content;
		to_light = vec3_normalize(vec3_subtract(light->pos, hit.pos));
		if (rt_is_light_visible(hit, light->pos, to_light, data))
		{
			color = rgb_add(color, rt_color_diffuse(hit, *light, to_light));
			color = rgb_add(color, rt_color_specular(hit, *light, to_light, \
				ray.dir));
		}
		light_node = light_node->next;
	}
	return (color);
}
