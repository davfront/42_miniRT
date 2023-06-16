/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_face.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/16 23:01:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_parse_obj_face_vertex(t_data *data, char *str, t_vec3 **v)
{
	unsigned int	id;
	t_list			*node;
	char			*sep;

	if (!data || !str || !v)
		rt_error_exit(data, "rt_parse_obj_face_vertex: no data");
	sep = ft_strchr(str, '/');
	if (sep)
		*sep = '\0';
	if (!rt_parse_uint(str, &id) || !id)
		rt_parse_value_error_exit(data, "face", "vertex index (int >= 1 required)", str);
	node = ft_lst_by_index(data->vertex_lst, id - 1);
	if (!node || !node->content)
		rt_parse_value_error_exit(data, "face", "vertex index (vertex not found)", str);
	*v = node->content;
}
void	rt_parse_obj_face(t_data *data, char **strs)
{
	t_obj			obj;
	t_vec3			v01;
	t_vec3			v02;
	t_obj			*content;
	t_list			*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "face: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "face: 3 arguments expected");
	obj.type = FACE;
	rt_parse_obj_face_vertex(data, strs[0], &obj.face.v[0]);
	rt_parse_obj_face_vertex(data, strs[1], &obj.face.v[1]);
	rt_parse_obj_face_vertex(data, strs[2], &obj.face.v[2]);
	v01 = vec3_subtract(*obj.face.v[1], *obj.face.v[0]);
	v02 = vec3_subtract(*obj.face.v[2], *obj.face.v[0]);
	obj.face.normal = vec3_cross(v01, v02);
	if (!vec3_length_squared(obj.face.normal))
		rt_parse_line_error_exit(data, "face: impossible to calculate a normal");
	obj.face.normal = vec3_normalize(obj.face.normal);
	obj.face.edge1 = vec3_subtract(*obj.face.v[1], *obj.face.v[0]);
	obj.face.edge2 = vec3_subtract(*obj.face.v[2], *obj.face.v[0]);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "face: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "face: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
