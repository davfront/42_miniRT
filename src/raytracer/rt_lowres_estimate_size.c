/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lowres_estimate_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 14:58:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_lowres_estimate_size(t_data *data)
{
	struct timeval	start;
	struct timeval	end;
	t_ray			ray;
	t_float			delta;
	int				size;

	gettimeofday(&start, NULL);
	ray = rt_get_view_ray(*data->cam, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	rt_get_closest_hit(data, ray);
	gettimeofday(&end, NULL);
	delta = (end.tv_sec - start.tv_sec) + \
				(end.tv_usec - start.tv_usec) / 1000000.0;
	size = sqrt(4 * 25 / (delta * WIN_WIDTH * WIN_HEIGHT));
	size = fmax(size, 1);
	size = fmin(size, 24);
	return (size);
}
