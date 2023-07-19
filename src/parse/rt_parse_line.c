/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 11:06:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_parse_line_values(t_data *data)
{
	if (ft_streq(data->strs[0], "A"))
		return (rt_parse_ambient_light(data, data->strs + 1));
	if (ft_streq(data->strs[0], "C"))
		return (rt_parse_camera(data, data->strs + 1));
	if (ft_streq(data->strs[0], "L"))
		return (rt_parse_light(data, data->strs + 1));
	if (ft_streq(data->strs[0], "pl"))
		return (rt_parse_obj_plane(data, data->strs + 1));
	if (ft_streq(data->strs[0], "sp"))
		return (rt_parse_obj_sphere(data, data->strs + 1));
	if (ft_streq(data->strs[0], "cy"))
		return (rt_parse_obj_cylinder(data, data->strs + 1));
	if (ft_streq(data->strs[0], "co"))
		return (rt_parse_obj_cone(data, data->strs + 1));
	if (data->strs[0])
		rt_parse_value_error_exit(data, NULL, "keyword", data->strs[0]);
}

void	rt_parse_line(t_data *data)
{
	char	*comment;

	if (!data || !data->line)
		rt_parse_line_error_exit(data, "no data");
	comment = ft_strchr(data->line, '#');
	if (comment)
		*comment = '\0';
	data->strs = ft_split(data->line, " \t\n");
	if (!data->strs)
		rt_parse_line_error_exit(data, "split failed");
	rt_parse_line_values(data);
	ft_free_split(&data->strs);
}
