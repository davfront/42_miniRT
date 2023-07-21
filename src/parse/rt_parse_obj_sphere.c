/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/21 00:51:50 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_obj_sphere(t_data *data, char **strs)
{
	t_obj	obj;
	t_obj	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "sphere: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "sphere: 3 arguments expected");
	obj.type = SPHERE;
	if (!rt_parse_vec3(strs[0], &obj.sphere.center))
		rt_parse_value_error_exit(data, "sphere", "center", strs[0]);
	if (!rt_parse_float_len(strs[1], &obj.sphere.radius))
		rt_parse_value_error_exit(data, "sphere", "diameter", strs[1]);
	obj.sphere.radius /= 2;
	if (!rt_parse_texture(strs[2], &obj))
		rt_parse_texture_error_exit(data, "sphere", strs[2]);
	obj.tf = rt_get_sphere_transformations(obj.sphere);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "sphere: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "sphere: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
