/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 13:18:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_px	rt_get_line_dists(t_line line)
{
	t_px	d;

	d.x = abs(line.p2.x - line.p1.x);
	d.y = abs(line.p2.y - line.p1.y);
	return (d);
}

static t_px	rt_get_line_dirs(t_line line)
{
	t_px	s;

	s.x = 2 * (line.p1.x < line.p2.x) - 1;
	s.y = 2 * (line.p1.y < line.p2.y) - 1;
	return (s);
}

void	rt_draw_line(t_data *data, t_line line, t_rgb color)
{	
	t_px	pi;
	t_px	d;
	t_px	s;
	int		err;
	int		err2;

	d = rt_get_line_dists(line);
	s = rt_get_line_dirs(line);
	err = d.x - d.y;
	pi = line.p1;
	while (pi.x != line.p2.x || pi.y != line.p2.y)
	{
		rt_draw_disc(data, disc(pi, line.thickness), color, 1);
		err2 = 2 * err;
		if (err2 > -d.y)
		{
			err -= d.y;
			pi.x += s.x;
		}
		if (err2 < d.x)
		{
			err += d.x;
			pi.y += s.y;
		}
	}
}

void	rt_draw_line_px(t_data *data, t_line line, t_rgb color, float alpha)
{	
	t_px	pi;
	t_px	d;
	t_px	s;
	int		err;
	int		err2;

	d = rt_get_line_dists(line);
	s = rt_get_line_dirs(line);
	err = d.x - d.y;
	pi = line.p1;
	while (pi.x != line.p2.x || pi.y != line.p2.y)
	{
		rt_draw_px(data, pi, color, alpha);
		err2 = 2 * err;
		if (err2 > -d.y)
		{
			err -= d.y;
			pi.x += s.x;
		}
		if (err2 < d.x)
		{
			err += d.x;
			pi.y += s.y;
		}
	}
}
