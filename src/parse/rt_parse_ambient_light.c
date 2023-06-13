/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/14 00:09:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_ambient_light(t_data *data, char **strs)
{
	t_al	*al;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "ambient light: no data");
	if (data->al)
		rt_parse_line_error_exit(data, "ambient light: cannot be set twice");
	if (rt_strs_len(strs) != 2)
		rt_parse_line_error_exit(data, "ambient light: 2 arguments expected");
	al = ft_calloc(1, sizeof(t_al));
	if (!al)
		rt_parse_line_error_exit(data, "ambient light: t_al alloc failed");
	if (!rt_parse_float_ratio(strs[0], &al->ratio))
		rt_parse_value_error_exit(data, "ambient light", "ratio", strs[0]);
	if (!rt_parse_rgb(strs[1], &al->color))
		rt_parse_value_error_exit(data, "ambient light", "color", strs[1]);
	al->computed = rgb_scale(al->color, al->ratio);
	data->al = al;
}
