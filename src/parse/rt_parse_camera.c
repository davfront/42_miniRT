/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:09:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_camera(char **strs, t_cam *cam_p)
{
	t_cam			cam;
	unsigned int	fov_deg;
	t_vec3			right;

	if (!cam_p || !strs || rt_strs_len(strs) != 3)
		return (0);
	if (!rt_parse_vec3(strs[0], &cam.pos))
		return (0);
	if (!rt_parse_vec3_dir(strs[1], &cam.dir))
		return (0);
	if (!rt_parse_uint(strs[2], &fov_deg) || fov_deg > 180)
		return (0);
	cam.fov = (t_float)fov_deg * M_PI / 180;
	cam.aspect_ratio = (t_float)WIN_WIDTH / WIN_HEIGHT;
	cam.up = vec3(0, 1, 0);
	right = vec3_cross(cam.dir, cam.up);
	if (vec3_length_squared(right) == 0)
	{
		cam.up = vec3(1, 0, 0);
		right = vec3_cross(cam.dir, cam.up);
	}
	cam.right = vec3_normalize(right);
	cam.top = vec3_normalize(vec3_cross(cam.right, cam.dir));
	*cam_p = cam;
	return (1);
}
