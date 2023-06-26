/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_update_fov.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 14:17:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_cam_update_fov(t_data *data, int delta_fov)
{
	int	fov;

	fov = (int)data->cam->fov + delta_fov;
	if (fov < 0 || fov > 180)
		return ;
	data->cam->fov = (unsigned int)fov;
	data->cam->proj = rt_cam_projection(data->cam->fov);
}
