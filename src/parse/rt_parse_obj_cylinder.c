/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 22:44:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_obj_cylinder(t_data *data, char **strs)
{
	t_obj	obj;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "cylinder: no data");
	if (rt_strs_len(strs) != 5)
		rt_parse_line_error_exit(data, "cylinder: 5 arguments expected");
	obj.type = CYLINDER;
	if (!rt_parse_vec3(strs[0], &obj.cylinder.center))
		rt_parse_value_error_exit(data, "cylinder", "center", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &obj.cylinder.axis))
		rt_parse_value_error_exit(data, "cylinder", "axis", strs[1]);
	if (!rt_parse_float_len(strs[2], &obj.cylinder.radius))
		rt_parse_value_error_exit(data, "cylinder", "diameter", strs[2]);
	obj.sphere.radius /= 2;
	if (!rt_parse_float_len(strs[3], &obj.cylinder.height))
		rt_parse_value_error_exit(data, "cylinder", "height", strs[3]);
	if (!rt_parse_rgb(strs[4], &obj.cylinder.color))
		rt_parse_value_error_exit(data, "cylinder", "color", strs[4]);
	data->objs_size++;
	data->objs[data->objs_size - 1] = obj;
}
