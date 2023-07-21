/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_viewer_thread_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:48:55 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/20 12:04:43 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_launch_threads(t_data *data)
{
	int			i;
	t_thread	*t;

	i = 0;
	while (i < THREAD_NB)
	{
		t = &data->rdr.thread[i];
		t->id = i + 1;
		t->data = data;
		if (pthread_create(&t->thread, 0, rt_lowres_draw_step_thread, t))
			rt_error_exit(data, 0);
		i++;
	}
}

static void	rt_wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < THREAD_NB)
	{
		if (pthread_join(data->rdr.thread[i].thread, NULL))
			rt_error_exit(data, 0);
		i++;
	}
}

void	rt_viewer_thread_handler(t_data *data)
{
	if (ENABLE_THREAD)
	{
		rt_launch_threads(data);
		rt_wait_for_threads(data);
	}
	else
		rt_lowres_draw_step(data, data->rdr.step);
}
