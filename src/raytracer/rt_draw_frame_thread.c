/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame_thread.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:49:37 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/21 22:26:29 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*rt_draw_frame_thread(void *tv)
{
	int			x;
	int			y;
	t_ray		ray;
	t_thread	*t;

	t = tv;
	x = ((WIN_WIDTH) * (t->id - 1) / THREAD_NB);
	while (x < ((WIN_WIDTH) * t->id) / THREAD_NB)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = rt_get_view_ray(*t->data->cam, x, y);
			ray.hit = rt_get_closest_hit(t->data, ray);
			if (ray.hit.obj)
				rt_viewer_draw_pixel(t->data, x, y, \
									rt_get_hit_color(t->data, ray));
			y++;
		}
		x++;
	}
	return (tv);
}
