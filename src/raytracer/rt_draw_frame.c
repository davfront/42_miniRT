/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/07 16:03:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_frame(t_data *data)
{
	int		x;
	int		y;
	// t_ray ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			rt_viewer_draw_pixel(data, x, y, WHITE);
			// ray = rt_get_view_ray(data->cam, x, y);
			y++;
		}
		x++;
	}
}
