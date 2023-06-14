/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_closest_hit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 18:46:10 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (new_hit.obj && new_hit.dist < hit.dist)
			hit = new_hit;
		i++;
	}
	return (hit);
}
