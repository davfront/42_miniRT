/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 23:49:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_light(t_data *data, char **strs)
{
	t_light	*light;
	t_list	*node;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "light: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "light: 3 arguments expected");
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		rt_parse_line_error_exit(data, "light: t_light alloc failed");
	if (!rt_parse_vec3(strs[0], &light->pos))
		rt_parse_value_error_exit(data, "light", "position", strs[0]);
	if (!rt_parse_float_ratio(strs[1], &light->ratio))
		rt_parse_value_error_exit(data, "light", "ratio", strs[1]);
	if (!rt_parse_rgb(strs[2], &light->color))
		rt_parse_value_error_exit(data, "light", "color", strs[2]);
	node = ft_lstnew(light);
	if (!node)
		rt_parse_line_error_exit(data, "light: t_list alloc failed");
	ft_lstadd_back(&data->light_lst, node);
}
