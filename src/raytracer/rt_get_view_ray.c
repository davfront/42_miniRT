/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_view_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/23 09:10:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rt_get_view_ray(t_cam cam, int x, int y)
{
	t_vec3	ndc;
	t_vec3	cam_space_dir;
	t_ray	ray;

	ndc.x = (2.0 / WIN_WIDTH * (x + 0.5) - 1.0);
	ndc.y = (1.0 - (2.0 / WIN_HEIGHT * (y + 0.5)));
	ndc.z = -1;
	cam_space_dir = rt_cam_ndc_to_camera_space(cam, ndc);
	ray.id = 0;
	ray.dir = mat4_multiply_axis(cam.c2w, cam_space_dir);
	ray.pos = mat4_multiply_vec3(cam.c2w, vec3(0, 0, 0));
	ray.hit = rt_hit_default();
	return (ray);
}
