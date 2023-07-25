/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_tex_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:12:18 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 14:11:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_get_tex_pixel(t_vec2	p, t_img xpm)
{
	char	*dst;
	int		color_int;
	int		x;
	int		y;

	if (!xpm.img)
		return (rgb_int(0));
	x = ((int)p.x % xpm.width + xpm.width) % xpm.width;
	y = ((int)p.y % xpm.height + xpm.height) % xpm.height;
	dst = xpm.addr;
	dst += y * xpm.len;
	dst += x * (xpm.bpp / 8);
	color_int = *(unsigned int *)dst;
	return (rgb_int(color_int));
}
