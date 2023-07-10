/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_c2s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/10 06:43:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_px	rt_cam_c2s(t_data *data, t_vec3 v)
{
	t_cam	cam;
	t_px	p;
	t_vec3	ndc;

	if (!data || !data->cam)
		return (px(-1, -1));
	cam = *data->cam;
	ndc = rt_cam_camera_space_to_ndc(cam, v);
	p.x = (ndc.x + 1.0) / 2 * WIN_WIDTH - 0.5;
	p.y = (1.0 - ndc.y) / 2 * WIN_HEIGHT - 0.5;
	return (p);
}
