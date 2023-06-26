/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_on_key_events.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 11:25:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_viewer_on_keydown(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		rt_viewer_on_close(data);
	if (keycode == KEY_PLUS)
		rt_cam_update_fov(data, 1);
	if (keycode == KEY_MINUS)
		rt_cam_update_fov(data, -1);
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		data->ui.changed = 1;
	return (0);
}

int	rt_viewer_on_keyup(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	return (0);
}
