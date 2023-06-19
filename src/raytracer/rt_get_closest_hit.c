/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_closest_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/19 14:15:23 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_get_closest_hit(t_data *data, t_ray ray)
{
	t_hit	hit;
	t_hit	new_hit;
	t_list	*obj_node;

	hit = rt_hit_default();
	if (!data)
		return (rt_error_exit(data, "rt_get_closest_hit: data is NULL"), hit);
	obj_node = data->obj_lst;
	while (obj_node)
	{
		new_hit = rt_get_obj_hit(ray, obj_node->content);
		if (new_hit.obj && new_hit.dist < hit.dist)
			hit = new_hit;
		obj_node = obj_node->next;
	}
	return (hit);
}
