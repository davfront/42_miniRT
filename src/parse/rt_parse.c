/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/20 15:53:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_check_scene(t_data *data)
{
	if (!data->al)
		rt_parse_line_error_exit(data, "no ambient light found");
	if (!data->cam)
		rt_parse_line_error_exit(data, "no camera found");
	if (!data->light_lst)
		rt_parse_line_error_exit(data, "no light found");
	if (!data->obj_lst)
		rt_parse_line_error_exit(data, "no object found");
}

void	rt_parse(t_data *data, int argc, char **argv)
{
	if (!data)
		rt_error_exit(data, "parsing: no data");
	rt_parse_input(data, argc, argv);
	data->fd = open(data->path, O_RDONLY);
	if (data->fd == -1)
		rt_error_exit(data, NULL);
	data->line = ft_gnl(data->fd);
	data->line_index++;
	while (data->line && data->line[0])
	{
		rt_parse_line(data);
		ft_free((void **)&(data->line));
		data->line = ft_gnl(data->fd);
		data->line_index++;
	}
	ft_free((void **)&(data->line));
	ft_free_gnl(data->fd);
	if (close(data->fd) == -1)
		rt_error_exit(data, NULL);
	data->fd = -1;
	data->line_index = 0;
	rt_check_scene(data);
}
