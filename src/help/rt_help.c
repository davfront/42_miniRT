/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 22:22:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_help_viewer(t_data *data, int line)
{
	int		i;

	rt_help_label(data, line++, "VIEWER");
	line++;
	rt_help_label(data, line, "FPS");
	rt_help_value_f(data, line++, data->rdr.fps, GREEN);
	if (LOW_RES_ENABLED)
	{
		rt_help_label(data, line, "Downscaling factor");
		rt_help_value_i(data, line++, data->rdr.tile_size, GREEN);
		rt_help_label(data, line, "Image quality");
		i = 100;
		if (data->rdr.tile_size > 1 && data->rdr.step_max > 0)
			i *= fmin(data->rdr.step, data->rdr.step_max) / data->rdr.step_max;
		if (i == 100)
			rt_help_value_perc(data, line++, i, GREEN);
		else
			rt_help_value_perc(data, line++, i, RED);
	}
	return (line);
}

static int	rt_help_camera(t_data *data, int line)
{
	t_vec3	v;

	rt_help_label(data, line++, "CAMERA");
	line++;
	rt_help_label(data, line, "FOV");
	rt_help_value_i(data, line++, data->cam->fov, GREEN);
	line++;
	v = rt_cam_pos(data->cam->c2w);
	rt_help_label(data, line, "Position X");
	rt_help_value_f(data, line++, v.x, GREEN);
	rt_help_label(data, line, "Position Y");
	rt_help_value_f(data, line++, v.y, GREEN);
	rt_help_label(data, line, "Position Z");
	rt_help_value_f(data, line++, v.z, GREEN);
	line++;
	v = rt_cam_dir(data->cam->c2w);
	rt_help_label(data, line, "Direction X");
	rt_help_value_f(data, line++, v.x, GREEN);
	rt_help_label(data, line, "Direction Y");
	rt_help_value_f(data, line++, v.y, GREEN);
	rt_help_label(data, line, "Direction Z");
	rt_help_value_f(data, line++, v.z, GREEN);
	return (line);
}

void	rt_help(t_data *data)
{
	int		line;

	if (!data->ui.help)
		return ;
	line = rt_help_viewer(data, 1);
	line += 2;
	if (!data->ui.selected)
		rt_help_camera(data, line);
	else
		rt_help_obj(data, *data->ui.selected, line);
}
