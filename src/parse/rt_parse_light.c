/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 22:44:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_light(t_data *data, char **strs)
{
	t_light	light;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "light: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "light: 3 arguments expected");
	if (!rt_parse_vec3(strs[0], &light.pos))
		rt_parse_value_error_exit(data, "light", "position", strs[0]);
	if (!rt_parse_float_ratio(strs[1], &light.ratio))
		rt_parse_value_error_exit(data, "light", "ratio", strs[1]);
	if (!rt_parse_rgb(strs[2], &light.color))
		rt_parse_value_error_exit(data, "light", "color", strs[2]);
	data->lights_size++;
	data->lights[data->lights_size - 1] = light;
}
