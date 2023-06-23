/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_print_fps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:19:26 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/23 14:57:06 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_print_fps(struct	timeval start_time, struct	timeval end_time)
{
	t_float	delta_time;

	delta_time = (end_time.tv_sec - start_time.tv_sec) + \
				(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
	printf("\033[0;33m");
	printf("fps : %f\n", 1 / delta_time);
	printf("\033M\033[2K\033[0m");
}
