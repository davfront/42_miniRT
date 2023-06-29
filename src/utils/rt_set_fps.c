/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:19:26 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/29 14:49:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_set_fps(t_data *data, struct timeval start, struct timeval end)
{
	t_float	delta;

	delta = (end.tv_sec - start.tv_sec) + \
				(end.tv_usec - start.tv_usec) / 1000000.0;
	if (data)
		data->rdr.fps = 1.0 / delta;
}
