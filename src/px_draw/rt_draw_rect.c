/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/24 16:08:31 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_rect(t_data *data, t_rect rect, t_rgb color, float alpha)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < rect.w)
	{
		j = 0;
		while (j < rect.h)
		{
			rt_draw_px(data, px(rect.p.x + i, rect.p.y + j), color, alpha);
			j++;
		}
		i++;
	}
}
