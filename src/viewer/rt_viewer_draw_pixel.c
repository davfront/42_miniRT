/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_draw_pixel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/09 17:29:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_viewer_draw_pixel(t_data *data, int x, int y, t_rgb color)
{
	char	*dst;
	int		color_int;

	if (x < 0 || x > WIN_WIDTH - 1)
		return ;
	if (y < 0 || y > WIN_HEIGHT - 1)
		return ;
	color_int = rgb_to_int(color);
	dst = data->img.addr;
	dst += y * data->img.len;
	dst += x * (data->img.bpp / 8);
	*(unsigned int *)dst = color_int;
}
