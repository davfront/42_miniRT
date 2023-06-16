/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:41:13 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/16 10:46:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_vertex(t_data *data, char **strs)
{
	t_vec3	vertex;
	t_vec3	*content;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "vertex: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "vertex: 3 arguments expected");
	if (!rt_parse_float(strs[0], &vertex.x))
		rt_parse_value_error_exit(data, "vertex", "x", strs[0]);
	if (!rt_parse_float(strs[1], &vertex.y))
		rt_parse_value_error_exit(data, "vertex", "y", strs[1]);
	if (!rt_parse_float(strs[2], &vertex.z))
		rt_parse_value_error_exit(data, "vertex", "x", strs[2]);
	content = ft_calloc(1, sizeof(t_vec3));
	if (!content)
		rt_parse_line_error_exit(data, "light: t_vec3 alloc failed");
	*content = vertex;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "vertices: t_list alloc failed");
	ft_lstadd_back(&data->vertex_lst, node);
}
