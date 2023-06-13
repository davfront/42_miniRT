/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 22:43:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_obj_sphere(t_data *data, char **strs)
{
	t_obj	obj;

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
	if (!rt_parse_rgb(strs[2], &obj.sphere.color))
		rt_parse_value_error_exit(data, "sphere", "color", strs[2]);
	data->objs_size++;
	data->objs[data->objs_size - 1] = obj;
}
