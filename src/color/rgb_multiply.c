/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_multiply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 19:54:59 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	rgb_multiply(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = rgb_clamp(round((float)c1.r * (float)c2.r / 255.0));
	res.g = rgb_clamp(round((float)c1.g * (float)c2.g / 255.0));
	res.b = rgb_clamp(round((float)c1.b * (float)c2.b / 255.0));
	return (res);
}
