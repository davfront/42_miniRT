/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_cs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:59:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 09:19:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	rt_cs_helper_color(t_data *data, int helper_id)
{
	if (data->ui.cs_helper_selected == -1 && \
		helper_id == data->ui.cs_helper_hovered)
		return (rgb_int(YELLOW));
	if (helper_id == data->ui.cs_helper_selected)
		return (rgb_int(YELLOW));
	if (helper_id == CS_MOV_X || helper_id == CS_ROT_X)
		return (rgb_int(CS_RED));
	if (helper_id == CS_MOV_Y || helper_id == CS_ROT_Y)
		return (rgb_int(CS_BLUE));
	if (helper_id == CS_MOV_Z || helper_id == CS_ROT_Z)
		return (rgb_int(CS_GREEN));
	return (rgb_int(GRAY));
}

static void	rt_draw_cs_mov(t_data *data, t_cs cs, int helper_id, t_rgb color)
{
	t_px	p1;
	t_px	p2;
	t_vec3	dir;

	if (helper_id == CS_MOV_X)
		dir = cs.dx;
	else if (helper_id == CS_MOV_Y)
		dir = cs.dy;
	else
		dir = cs.dz;
	p1 = rt_cam_c2s(data, vec3_add(cs.center, vec3_scale(dir, CS_POINT_RAD)));
	p2 = cs.helper_px[helper_id];
	rt_draw_line(data, line(p1, p2, 2), color);
	rt_draw_disc(data, disc(p2, CS_POINT_RAD), color, 1);
}

static void	rt_draw_cs_rot_arc(t_data *data, t_cs cs, t_vec3 arc_dir[2], \
	t_rgb color)
{
	t_line	line;
	int		i;
	t_float	angle;
	t_vec3	dir;

	line.thickness = 2;
	i = 0;
	while (i < 8)
	{
		angle = M_PI / 2 / 8;
		dir = vec3_add(vec3_scale(arc_dir[0], cos(angle * i)), \
			vec3_scale(arc_dir[1], sin(angle * i)));
		line.p1 = rt_cam_c2s(data, \
			vec3_add(cs.center, vec3_scale(dir, CS_ROT_LEN)));
		dir = vec3_add(vec3_scale(arc_dir[0], cos(angle * (i + 1))), \
			vec3_scale(arc_dir[1], sin(angle * (i + 1))));
		line.p2 = rt_cam_c2s(data, \
			vec3_add(cs.center, vec3_scale(dir, CS_ROT_LEN)));
		rt_draw_line(data, line, color);
		i++;
	}
}

static void	rt_draw_cs_rot(t_data *data, t_cs cs, int helper_id, t_rgb color)
{
	t_vec3	arc_dir[2];

	rt_draw_disc(data, disc(cs.helper_px[helper_id], CS_POINT_RAD), color, 1);
	if (helper_id == CS_ROT_X)
	{
		arc_dir[0] = cs.dz;
		arc_dir[1] = cs.dy;
	}
	else if (helper_id == CS_ROT_Y)
	{
		arc_dir[0] = cs.dx;
		arc_dir[1] = cs.dz;
	}
	else
	{
		arc_dir[0] = cs.dy;
		arc_dir[1] = cs.dx;
	}
	rt_draw_cs_rot_arc(data, cs, arc_dir, color);
}

void	rt_draw_cs(t_data *data, t_cs cs)
{
	int		i;
	int		helper_id;
	t_rgb	color;

	i = 0;
	while (i < CS_SIZE)
	{
		helper_id = cs.ordered_helper_types[i];
		color = rt_cs_helper_color(data, helper_id);
		if (helper_id == CS_ORIG)
			rt_draw_disc(data, \
				disc(cs.helper_px[CS_ORIG], CS_POINT_RAD), color, 1);
		if (helper_id == CS_MOV_X \
			|| helper_id == CS_MOV_Y \
			|| helper_id == CS_MOV_Z)
			rt_draw_cs_mov(data, cs, helper_id, color);
		if (helper_id == CS_ROT_X \
			|| helper_id == CS_ROT_Y \
			|| helper_id == CS_ROT_Z)
			rt_draw_cs_rot(data, cs, helper_id, color);
		i++;
	}
}
