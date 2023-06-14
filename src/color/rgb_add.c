/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:41:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 19:51:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	rgb_add(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = rgb_clamp((int)c1.r + (int)c2.r);
	res.g = rgb_clamp((int)c1.g + (int)c2.g);
	res.b = rgb_clamp((int)c1.b + (int)c2.b);
	return (res);
}
