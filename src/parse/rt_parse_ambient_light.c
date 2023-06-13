/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ambient_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:10:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_ambient_light(char **strs, t_al *al_p)
{
	t_al	al;

	if (!al_p || !strs || rt_strs_len(strs) != 2)
		return (0);
	if (!rt_parse_float_ratio(strs[0], &al.ratio))
		return (0);
	if (!rt_parse_rgb(strs[1], &al.color))
		return (0);
	al.computed = rgb_scale(al.color, al.ratio);
	*al_p = al;
	return (1);
}
