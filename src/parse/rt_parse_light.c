/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:15:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_light(char **strs, t_light *light_p)
{
	t_light	light;

	if (!light_p || !strs || rt_strs_len(strs) != 3)
		return (0);
	if (!rt_parse_vec3(strs[0], &light.pos))
		return (0);
	if (!rt_parse_float_ratio(strs[1], &light.ratio))
		return (0);
	if (!rt_parse_rgb(strs[2], &light.color))
		return (0);
	*light_p = light;
	return (1);
}
