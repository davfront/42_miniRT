/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/16 23:12:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_frame(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;

	x = 0;
	printf("Creating image (0%%)\n");
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
		if ((x + 1) * (y + 1) % 10 == 0)
			printf("\033[2K\033[ACreating image (%i%%)\n", (x + 1) * (y + 1) * 100 / (WIN_WIDTH * WIN_HEIGHT));
		x++;
	}
	printf("\033[2K\033[ACreating image (100%%)\n");
}
