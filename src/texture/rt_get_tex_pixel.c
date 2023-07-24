/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_tex_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:07:43 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/24 16:07:44 by atchougo         ###   ########.fr       */
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
	x = (int)floor(p.x * (float)xpm.width) % xpm.width;
	y = (int)floor(p.y * (float)xpm.height) % xpm.height;
	dst = xpm.addr;
	dst += y * xpm.len;
	dst += x * (xpm.bpp / 8);
	color_int = *(unsigned int *)dst;
	return (rgb_int(color_int));
}
