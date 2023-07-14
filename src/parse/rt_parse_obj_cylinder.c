/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/15 00:03:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_parse_obj_cylinder_calcul_values(t_data *data, t_obj *obj)
{
	t_vec3	displacement;

	if (!data || !obj)
		return ;
	displacement = vec3_scale(obj->cylinder.axis, obj->cylinder.height / 2);
	obj->cylinder.top = vec3_add(obj->cylinder.center, displacement);
	obj->cylinder.bot = vec3_subtract(obj->cylinder.center, displacement);
	obj->cylinder.vec_height = vec3_subtract(obj->cylinder.top,\
											 obj->cylinder.bot);
	obj->cylinder.vec_h_square = vec3_dot(obj->cylinder.vec_height,\
										obj->cylinder.vec_height);
}

static void	rt_parse_obj_cylinder_values(t_data *data, char **strs, t_obj *obj)
{
	if (!data || !strs || !obj)
		return ;
	obj->type = CYLINDER;
	if (!rt_parse_vec3(strs[0], &obj->cylinder.center))
		rt_parse_value_error_exit(data, "cylinder", "center", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &obj->cylinder.axis))
		rt_parse_value_error_exit(data, "cylinder", "axis", strs[1]);
	if (!rt_parse_float_len(strs[2], &obj->cylinder.radius))
		rt_parse_value_error_exit(data, "cylinder", "diameter", strs[2]);
	obj->sphere.radius /= 2;
	if (!rt_parse_float_len(strs[3], &obj->cylinder.height))
		rt_parse_value_error_exit(data, "cylinder", "height", strs[3]);
	if (!rt_parse_rgb(strs[4], &obj->cylinder.color))
		rt_parse_value_error_exit(data, "cylinder", "color", strs[4]);
}

void	rt_parse_obj_cylinder(t_data *data, char **strs)
{
	t_obj	obj;
	t_obj	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "cylinder: no data");
	if (rt_strs_len(strs) != 5)
		rt_parse_line_error_exit(data, "cylinder: 5 arguments expected");
	rt_parse_obj_cylinder_values(data, strs, &obj);
	rt_parse_obj_cylinder_calcul_values(data, &obj);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "cylinder: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "cylinder: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
	rt_parse_obj_cyl_plane(data, obj);
}
