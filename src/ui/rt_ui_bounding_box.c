/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ui_bounding_box.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:59:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 14:31:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_ui_bounding_box_get_vertices(t_data *data, t_obj_type type, \
	t_mat4 mt, t_px p[8])
{
	t_vec3	bbox[2];
	t_vec3	flag;
	t_vec3	v;
	int		i;

	bbox[0] = vec3(-1, -1, -1);
	bbox[1] = vec3(1, 1, 1);
	if (type == CONE)
		bbox[0].y = 0;
	flag = vec3(0, 0, 0);
	i = 0;
	while (i < 8)
	{
		if (i % 1 == 0)
			flag.x = 1 - flag.x;
		if (i % 2 == 0)
			flag.y = 1 - flag.y;
		if (i % 4 == 0)
			flag.z = 1 - flag.z;
		v.x = bbox[0].x * (1 - flag.x) + bbox[1].x * flag.x;
		v.y = bbox[0].y * (1 - flag.y) + bbox[1].y * flag.y;
		v.z = bbox[0].z * (1 - flag.z) + bbox[1].z * flag.z;
		p[i] = rt_cam_w2s(data, mat4_multiply_vec3(mt, v));
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
	rt_ui_bounding_box_get_vertices(data, obj->type, tf_to_mat4(obj->tf), p);
	rt_ui_bounding_box_draw_lines(data, p);
}
