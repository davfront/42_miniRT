/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:26 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 21:06:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	rgb_scale(t_rgb c, float ratio)
{
	t_rgb	res;

	ratio = fmin(fmax(ratio, 0), 1);
	res.r = rgb_clamp(round((float)c.r * ratio));
	res.g = rgb_clamp(round((float)c.g * ratio));
	res.b = rgb_clamp(round((float)c.b * ratio));
	return (res);
}
