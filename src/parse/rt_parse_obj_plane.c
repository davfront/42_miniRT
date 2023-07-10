/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/10 10:29:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_mat4	rt_get_plane_transformation_matrix(t_plane pl)
{
	t_vec3	up;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	top;
	t_mat4	mt;

	up = vec3(0, 1, 0);
	top = pl.normal;
	right = vec3(1, 0, 0);
	if (vec3_length_squared(vec3_cross(up, top)) != 0)
		right = vec3_normalize(vec3_cross(up, top));
	forward = vec3_normalize(vec3_cross(right, top));
	mt = mat4_identity();
	mt.m[0][0] = right.x;
	mt.m[1][0] = right.y;
	mt.m[2][0] = right.z;
	mt.m[0][1] = top.x;
	mt.m[1][1] = top.y;
	mt.m[2][1] = top.z;
	mt.m[0][2] = forward.x;
	mt.m[1][2] = forward.y;
	mt.m[2][2] = forward.z;
	mt = mat4_translate(mt, pl.point);
	return (mt);
}

void	rt_parse_obj_plane(t_data *data, char **strs)
{
	t_obj	obj;
	t_obj	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "plane: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "plane: 3 arguments expected");
	obj.type = PLANE;
	if (!rt_parse_vec3(strs[0], &obj.plane.point))
		rt_parse_value_error_exit(data, "plane", "point", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &obj.plane.normal))
		rt_parse_value_error_exit(data, "plane", "normal", strs[1]);
	if (!rt_parse_rgb(strs[2], &obj.plane.color))
		rt_parse_value_error_exit(data, "plane", "color", strs[2]);
	obj.mt = rt_get_plane_transformation_matrix(obj.plane);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "plane: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "plane: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
