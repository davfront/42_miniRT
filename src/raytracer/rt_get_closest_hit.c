/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_closest_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 14:16:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit	rt_get_obj_hit(t_ray ray, t_obj *obj)
{
	if (!obj)
		return (rt_hit_default());
	if (obj->type == SPHERE)
		return (rt_get_sphere_hit(ray, obj));
	return (rt_hit_default());
}

t_hit	rt_get_closest_hit(t_data *data, t_ray ray)
{
	size_t	i;
	t_hit	hit;
	t_hit	new_hit;

	hit = rt_hit_default();
	if (!data)
		return (hit);
	i = 0;
	while (i < data->objs_size)
	{
		new_hit = rt_get_obj_hit(ray, &data->objs[i]);
		if (new_hit.obj && (!hit.obj || new_hit.dist < hit.dist))
			hit = new_hit;
		i++;
	}
	return (hit);
}
