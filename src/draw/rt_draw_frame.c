/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/06 15:18:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_frame(t_data *data)
{
	int y;
	int	z;

	y = 0;
	while (y < WIN_WIDTH)
	{
		z = 0;
		while (z < WIN_HEIGHT)
		{
			rt_draw_pixel(data, y, z, WHITE);
			z++;
		}
		y++;
	}
}
