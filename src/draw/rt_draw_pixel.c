/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/06 15:19:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_WIDTH - 1)
		return ;
	if (y < 0 || y > WIN_HEIGHT - 1)
		return ;
	dst = data->img.addr;
	dst += y * data->img.len;
	dst += x * (data->img.bpp / 8);
	*(unsigned int *)dst = color;
}
