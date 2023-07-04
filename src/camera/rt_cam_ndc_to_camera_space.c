/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_ndc_to_camera_space.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:34:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/04 10:38:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_cam_ndc_to_camera_space(t_cam cam, t_vec3 ndc)
{
	t_vec3	v;

	v.x = ndc.x * (-ndc.z) * (cam.aspect_ratio * cam.tan_half_fov);
	v.y = ndc.y * (-ndc.z) * cam.tan_half_fov;
	v.z = ndc.z;
	return (v);
}
