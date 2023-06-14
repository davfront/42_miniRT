/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/14 23:50:06 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_parse_obj_camera_values(t_data *data, char **strs, t_cam *cam)
{
	unsigned int	fov_deg;

	if (!data || !strs || !cam)
		return ;
	if (!rt_parse_vec3(strs[0], &cam->pos))
		rt_parse_value_error_exit(data, "camera", "position", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &cam->dir))
		rt_parse_value_error_exit(data, "camera", "direction", strs[1]);
	if (!rt_parse_uint(strs[2], &fov_deg) || fov_deg > 180)
		rt_parse_value_error_exit(data, "camera", "fov", strs[2]);
	cam->fov = (t_float)fov_deg * M_PI / 180;
	cam->aspect_ratio = (t_float)WIN_WIDTH / WIN_HEIGHT;
	cam->up = vec3(0, 1, 0);
	cam->right = vec3_cross(cam->dir, cam->up);
	if (vec3_length_squared(cam->right) == 0)
	{
		cam->up = vec3(1, 0, 0);
		cam->right = vec3_cross(cam->dir, cam->up);
	}
	cam->right = vec3_normalize(cam->right);
	cam->top = vec3_normalize(vec3_cross(cam->right, cam->dir));
}

void	rt_parse_camera(t_data *data, char **strs)
{
	t_cam			cam;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "camera: no data");
	if (data->cam)
		rt_parse_line_error_exit(data, "camera: cannot be set twice");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "camera: 3 arguments expected");
	rt_parse_obj_camera_values(data, strs, &cam);
	data->cam = ft_calloc(1, sizeof(t_cam));
	if (!data->cam)
		rt_parse_line_error_exit(data, "camera: t_cam alloc failed");
	*data->cam = cam;
}
