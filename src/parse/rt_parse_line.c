/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:42:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_parse_line_values(t_data *data, char **strs)
{
	t_light	*light_p;
	t_obj	*obj_p;

	if (!strs)
		return (0);
	if (!rt_strs_len(strs))
		return (1);
	if (ft_streq(strs[0], "A"))
		return (rt_parse_ambient_light(strs + 1, &data->al));
	if (ft_streq(strs[0], "C"))
		return (rt_parse_camera(strs + 1, &data->cam));
	if (ft_streq(strs[0], "L"))
	{
		data->lights_size++;
		light_p = &data->lights[data->lights_size - 1];
		return (rt_parse_light(strs + 1, light_p));
	}
	if (ft_streq(strs[0], "pl"))
	{
		data->objs_size++;
		obj_p = &data->objs[data->objs_size - 1];
		return (rt_parse_obj_plane(strs + 1, obj_p));
	}
	if (ft_streq(strs[0], "cy"))
	{
		data->objs_size++;
		obj_p = &data->objs[data->objs_size - 1];
		return (rt_parse_obj_cylinder(strs + 1, obj_p));
	}
	if (ft_streq(strs[0], "sp"))
	{
		data->objs_size++;
		obj_p = &data->objs[data->objs_size - 1];
		return (rt_parse_obj_sphere(strs + 1, obj_p));
	}
	return (0);
}

int	rt_parse_line(t_data *data, char *line)
{
	char	**strs;
	int		ret;

	if (!data || !line)
		return (0);
	strs = ft_split(line, " \t\n");
	ret = rt_parse_line_values(data, strs);
	ft_free_split(strs);
	return (ret);
}
