/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/17 16:30:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

void	rt_draw_frame(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	clock_t	start;
    double	time_now;
    double	time_estimated;

	start = clock();
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
		{
			time_now = ((double) (clock() - start)) / CLOCKS_PER_SEC;
			time_estimated = time_now * WIN_WIDTH * WIN_HEIGHT / ((x + 1) * (y + 1));
			printf("\033[2K\033[ACreating image (%i%%) - %is / %is\n", (x + 1) * (y + 1) * 100 / (WIN_WIDTH * WIN_HEIGHT), (int)time_now, (int)time_estimated);
		}
		x++;
	}
	time_now = ((double) (clock() - start)) / CLOCKS_PER_SEC;
	printf("\033[2K\033[ACreating image (100%%) - %is / %is\n", (int)time_now, (int)time_now);
}
