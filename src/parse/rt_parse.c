/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 21:57:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	close(data->fd);
	data->fd = -1;
}
