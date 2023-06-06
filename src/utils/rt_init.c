/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/07 00:35:34 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_init(t_data *data)
{
	if (!data)
		return ;
	data->path = NULL;
	data->title = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img.img = NULL;
	data->img.addr = NULL;
	data->al.color = rgb(0, 0, 0);
	data->al.ratio = 0;
	data->cam.pos = vec3(0, 0, 0);
	data->cam.dir = vec3(0, 0, 0);
	data->cam.fov = 0;
	data->lights_size = 0;
	data->lights = NULL;
	data->objs_size = 0;
	data->objs = NULL;
}
