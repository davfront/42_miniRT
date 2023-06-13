/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:21:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));

	// Todo: replace by chained list
	data.lights_size = 0;
	data.lights = calloc(5, sizeof(t_light));
	if (!data.lights)
		rt_error_exit(&data, "lights: alloc failed");

	// Todo: replace by chained list
	data.objs_size = 0;
	data.objs = calloc(10, sizeof(t_obj));
	if (!data.objs)
		rt_error_exit(&data, "objs: alloc failed");

	rt_parse(&data, argc, argv);
	rt_viewer_start(&data);
	rt_delete(&data);
	return (EXIT_SUCCESS);
}
