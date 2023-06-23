/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_view_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 20:30:14 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rt_get_view_ray(t_cam cam, int x, int y)
{
	t_float	ndc_x;
	t_float	ndc_y;
	t_ray	ray;

	ndc_x = (2.0 / WIN_WIDTH * (x + 0.5) - 1.0);
	ndc_y = (1.0 - (2.0 / WIN_HEIGHT * (y + 0.5)));
	ray.dir = mat4_multiply_vec3(cam.proj, vec3(ndc_x, ndc_y, -1));
	ray.dir = mat4_multiply_axis(cam.c2w_mouse, ray.dir);
	ray.pos = mat4_multiply_vec3(cam.c2w_mouse, vec3(0, 0, 0));
	ray.hit = rt_hit_default();
	return (ray);
}
