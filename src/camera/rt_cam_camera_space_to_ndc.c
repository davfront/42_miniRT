/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_camera_space_to_ndc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/04 10:40:37 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_cam_camera_space_to_ndc(t_cam cam, t_vec3 v)
{
	t_vec3	ndc;

	ndc.x = v.x / (-v.z * cam.tan_half_fov * cam.aspect_ratio);
	ndc.y = v.y / (-v.z * cam.tan_half_fov);
	ndc.z = v.z;
	return (ndc);
}
