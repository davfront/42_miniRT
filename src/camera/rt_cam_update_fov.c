/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_update_fov.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/04 10:05:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_cam_update_fov(t_data *data, int delta_fov)
{
	int		fov;
	t_float	fov_rad;

	fov = (int)data->cam->fov + delta_fov;
	if (fov < 0 || fov > 180)
		return ;
	data->cam->fov = (unsigned int)fov;
	fov_rad = (t_float)fov * M_PI / 180;
	data->cam->tan_half_fov = tan(fov_rad / 2);
}
