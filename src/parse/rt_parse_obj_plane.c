/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/15 00:03:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "plane: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "plane: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
