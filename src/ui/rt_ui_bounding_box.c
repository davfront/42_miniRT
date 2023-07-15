/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ui_bounding_box.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:59:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/13 16:47:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_ui_bounding_box_get_vertices(t_data *data, t_mat4 mt, t_px p[8])
{
	t_vec3	v;
	int		i;

	i = 0;
	while (i < 8)
	{
		v = mat4_multiply_vec3(mt, \
			vec3(pow(-1, i), pow(-1, i / 2), pow(-1, i / 4)));
		p[i] = rt_cam_w2s(data, v);
		i++;
	}
}

static void	rt_ui_bounding_box_draw_lines(t_data *data, t_px p[8])
{
	t_rgb	color;

	color = rgb_int(GRAY);
	rt_draw_line_px(data, line(p[0], p[1], 1), color, 1);
	rt_draw_line_px(data, line(p[0], p[2], 1), color, 1);
	rt_draw_line_px(data, line(p[1], p[3], 1), color, 1);
	rt_draw_line_px(data, line(p[2], p[3], 1), color, 1);
	rt_draw_line_px(data, line(p[4], p[5], 1), color, 1);
	rt_draw_line_px(data, line(p[4], p[6], 1), color, 1);
	rt_draw_line_px(data, line(p[5], p[7], 1), color, 1);
	rt_draw_line_px(data, line(p[6], p[7], 1), color, 1);
	rt_draw_line_px(data, line(p[0], p[4], 1), color, 1);
	rt_draw_line_px(data, line(p[1], p[5], 1), color, 1);
	rt_draw_line_px(data, line(p[2], p[6], 1), color, 1);
	rt_draw_line_px(data, line(p[3], p[7], 1), color, 1);
}

void	rt_ui_bounding_box(t_data *data, t_obj *obj)
{
	t_px	p[8];

	if (!obj || obj->type == PLANE)
		return ;
	rt_ui_bounding_box_get_vertices(data, tf_to_mat4(obj->tf), p);
	rt_ui_bounding_box_draw_lines(data, p);
}
