/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:57:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse(t_data *data, int argc, char **argv)
{
	int		fd;
	char	*line;
	int		parse_line_failed;

	if (!data)
		rt_error_exit(data, "rt_parse: data is NULL");
	rt_parse_input(data, argc, argv);
	fd = open(data->path, O_RDONLY);
	if (fd == -1)
		rt_error_exit(data, NULL);
	parse_line_failed = 0;
	line = ft_gnl(fd);
	while (!parse_line_failed && line && *line)
	{
		parse_line_failed = !rt_parse_line(data, line);
		ft_free((void **)&line);
		line = ft_gnl(fd);
	}
	ft_free((void **)&line);
	ft_free_gnl(fd);
	if (close(fd) == -1)
		rt_error_exit(data, NULL);
	if (parse_line_failed)
		rt_exit(data);
}
