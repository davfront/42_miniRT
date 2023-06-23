/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 17:21:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_projection(unsigned int fov)
{
	t_float	aspect_ratio;
	t_float	fov_rad;
	t_float	tan_half_fov;
	t_mat4	result;

	aspect_ratio = (t_float)WIN_WIDTH / WIN_HEIGHT;
	fov_rad = fov * M_PI / 180;
	tan_half_fov = tan(fov_rad / 2);
	result = mat4_identity();
	result.m[0][0] = aspect_ratio * tan_half_fov;
	result.m[1][1] = tan_half_fov;
	return (result);
}
