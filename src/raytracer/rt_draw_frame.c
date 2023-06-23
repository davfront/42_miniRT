/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/24 00:38:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_frame(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = rt_get_view_ray(*data->cam, x, y);
			ray.hit = rt_get_closest_hit(data, ray);
			if (ray.hit.obj)
				rt_viewer_draw_pixel(data, x, y, rt_get_hit_color(data, ray));
			y++;
		}
		x++;
	}
}
