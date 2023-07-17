/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 10:22:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_on_scroll(t_data *data, int is_up)
{
	int	dir;

	if (!data || !data->cam)
		return ;
	dir = 2 * is_up - 1;
	rt_cam_update_c2w(data, \
		rt_cam_to_world_translate(data->cam->c2w, vec3(0, 0, dir), 10));
	data->ui.changed = 1;
}
