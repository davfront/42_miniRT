/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_disc_hit_dist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 10:14:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_float	rt_get_disc_hit_dist(t_ray ray, t_disc3 disc, t_float t_max)
{
	t_float	t;
	t_float	denom;
	t_float	num;
	t_vec3	v;

	denom = vec3_dot(ray.dir, disc.axis);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	num = vec3_dot(vec3_subtract(disc.center, ray.pos), disc.axis);
	t = num / denom;
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (INFINITY);
	v = vec3_subtract(vec3_add(ray.pos, vec3_scale(ray.dir, t)), disc.center);
	if (vec3_length_squared(v) > pow(disc.radius, 2))
		return (INFINITY);
	return (t);
}
