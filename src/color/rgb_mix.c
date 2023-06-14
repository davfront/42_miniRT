/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_mix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:26 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 19:54:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	rgb_mix(t_rgb c1, t_rgb c2, float ratio)
{
	t_rgb	res;

	ratio = fmin(fmax(ratio, 0), 1);
	res.r = rgb_clamp(round((1.0 - ratio) * (float)c1.r + ratio * (float)c2.r));
	res.g = rgb_clamp(round((1.0 - ratio) * (float)c1.g + ratio * (float)c2.g));
	res.b = rgb_clamp(round((1.0 - ratio) * (float)c1.b + ratio * (float)c2.b));
	return (res);
}
