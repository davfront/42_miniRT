/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_disc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 11:59:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_draw_disc(t_data *data, t_disc disc, t_rgb color, float alpha)
{
	t_px	p;
	t_float	d;

	if (!data)
		return ;
	p.x = disc.center.x - disc.radius;
	while (p.x <= disc.center.x + (int)disc.radius)
	{
		p.y = disc.center.y - disc.radius;
		while (p.y <= disc.center.y + (int)disc.radius)
		{
			d = sqrt(pow(p.x - disc.center.x, 2) + pow(p.y - disc.center.y, 2));
			if (d < (t_float)disc.radius)
				rt_draw_px(data, p, color, alpha);
			p.y++;
		}
		p.x++;
	}
}
