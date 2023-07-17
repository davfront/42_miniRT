/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_px.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 13:18:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_px(t_data *data, t_px p, t_rgb color, float alpha)
{
	t_rgb	c0;
	t_rgb	c1;

	if (alpha == 1)
	{
		rt_viewer_set_pixel(data, p.x, p.y, color);
		return ;
	}
	c0 = rt_viewer_get_pixel(data, p.x, p.y);
	c1 = rgb_mix(c0, color, alpha);
	rt_viewer_set_pixel(data, p.x, p.y, c1);
}
