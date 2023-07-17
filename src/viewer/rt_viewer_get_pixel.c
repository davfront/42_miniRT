/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_set_pixel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 11:52:32 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_viewer_get_pixel(t_data *data, int x, int y)
{
	char	*dst;
	int		color_int;

	if (!data)
		return (rgb(0, 0, 0));
	if (x < 0 || x > WIN_WIDTH - 1)
		return (rgb(0, 0, 0));
	if (y < 0 || y > WIN_HEIGHT - 1)
		return (rgb(0, 0, 0));
	dst = data->img.addr;
	dst += y * data->img.len;
	dst += x * (data->img.bpp / 8);
	color_int = *(unsigned int *)dst;
	return (rgb_int(color_int));
}
