/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ui_selected.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:59:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/13 16:47:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_order_obj_cs_helpers(t_vec3 v[CS_SIZE], int *id)
{
	int		i;
	int		j;
	int		temp;

	i = -1;
	while (i++ < CS_SIZE)
		id[i] = i;
	i = 0;
	while (i < CS_SIZE - 1)
	{
		j = i + 1;
		while (j < CS_SIZE)
		{
			if (v[id[j]].z < v[id[i]].z)
			{
				temp = id[i];
				id[i] = id[j];
				id[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	rt_init_obj_cs_helpers(t_data *data, t_cs *cs)
{
	t_vec3	v[CS_SIZE];
	t_vec3	dir;
	int		i;

	v[CS_ORIG] = cs->center;
	v[CS_MOV_X] = vec3_add(cs->center, vec3_scale(cs->dx, CS_MOV_LEN));
	v[CS_MOV_Y] = vec3_add(cs->center, vec3_scale(cs->dy, CS_MOV_LEN));
	v[CS_MOV_Z] = vec3_add(cs->center, vec3_scale(cs->dz, CS_MOV_LEN));
	dir = vec3_scale(vec3_add(cs->dy, cs->dz), cos(M_PI / 4));
	v[CS_ROT_X] = vec3_add(cs->center, vec3_scale(dir, CS_ROT_LEN));
	dir = vec3_scale(vec3_add(cs->dz, cs->dx), cos(M_PI / 4));
	v[CS_ROT_Y] = vec3_add(cs->center, vec3_scale(dir, CS_ROT_LEN));
	dir = vec3_scale(vec3_add(cs->dx, cs->dy), cos(M_PI / 4));
	v[CS_ROT_Z] = vec3_add(cs->center, vec3_scale(dir, CS_ROT_LEN));
	i = 0;
	while (i < CS_SIZE)
	{
		cs->helper_px[i] = rt_cam_c2s(data, v[i]);
		i++;
	}
	rt_order_obj_cs_helpers(v, cs->ordered_helper_types);
}

static t_cs	rt_get_obj_cs(t_data *data, t_obj *obj)
{
	t_cs	cs;
	t_mat4	o2c;
	t_float	dir_scale;

	o2c = mat4_multiply_rev(tf_to_mat4(obj->tf), data->cam->w2c);
	cs.center = mat4_multiply_vec3(o2c, vec3(0, 0, 0));
	dir_scale = -cs.center.z * data->cam->tan_half_fov * 2 / WIN_HEIGHT;
	cs.dx = vec3_scale(mat4_multiply_axis(o2c, vec3(0, 0, 1)), dir_scale);
	cs.dy = vec3_scale(mat4_multiply_axis(o2c, vec3(0, 1, 0)), dir_scale);
	cs.dz = vec3_scale(mat4_multiply_axis(o2c, vec3(-1, 0, 0)), dir_scale);
	rt_init_obj_cs_helpers(data, &cs);
	return (cs);
}

void	rt_ui_selected(t_data *data)
{
	t_cs	cs;

	if (!data || !data->ui.selected)
		return ;
	rt_ui_bounding_box(data, data->ui.selected);
	cs = rt_get_obj_cs(data, data->ui.selected);
	rt_draw_cs(data, cs);
	data->ui.cs = cs;
}
