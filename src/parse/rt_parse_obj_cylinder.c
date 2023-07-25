/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/23 09:38:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	obj->cylinder.radius /= 2;
	if (!rt_parse_float_len(strs[3], &obj->cylinder.height))
		rt_parse_value_error_exit(data, "cylinder", "height", strs[3]);
	if (!rt_parse_texture(data, strs[4], obj))
		rt_parse_texture_error_exit(data, "cylinder", strs[4]);
	if (!rt_parse_material(strs[5], &obj->mtl))
		rt_parse_value_error_exit(data, "cylinder", "material", strs[5]);
}

void	rt_parse_obj_cylinder(t_data *data, char **strs)
{
	int		arg_count;
	t_obj	obj;
	t_obj	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "cylinder: no data");
	arg_count = rt_strs_len(strs);
	if (arg_count < 5 && arg_count > 6)
		rt_parse_line_error_exit(data, \
			"cylinder: 5 arguments expected (+ optional material argument)");
	rt_parse_obj_cylinder_values(data, strs, &obj);
	obj.tf = rt_get_cylinder_transformations(obj.cylinder);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "cylinder: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "cylinder: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
