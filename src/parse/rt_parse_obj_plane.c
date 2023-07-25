/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 14:24:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_parse_obj_plane_values(t_data *data, char **strs, t_obj *obj)
{
	if (!data || !strs || !obj)
		return ;
	obj->type = PLANE;
	if (!rt_parse_vec3(strs[0], &obj->plane.point))
		rt_parse_value_error_exit(data, "plane", "point", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &obj->plane.normal))
		rt_parse_value_error_exit(data, "plane", "normal", strs[1]);
	if (!rt_parse_texture(data, strs[2], obj))
		rt_parse_texture_error_exit(data, "plane", strs[2]);
	if (!rt_parse_material(strs[3], &obj->mtl))
		rt_parse_value_error_exit(data, "plane", "material", strs[3]);
}

void	rt_parse_obj_plane(t_data *data, char **strs)
{
	int		arg_count;
	t_obj	obj;
	t_obj	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "plane: no data");
	arg_count = rt_strs_len(strs);
	if (arg_count < 3 && arg_count > 4)
		rt_parse_line_error_exit(data, \
			"plane: 3 arguments expected (+ optional material argument)");
	rt_parse_obj_plane_values(data, strs, &obj);
	obj.tf = rt_get_plane_transformations(obj.plane);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "plane: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "plane: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
