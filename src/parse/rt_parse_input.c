/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:58:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 15:30:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_input(t_data *data, int argc, char **argv)
{
	char		*path;
	char		*filename;
	char		*extension;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene.rt>\n", STDERR_FILENO);
		rt_exit(data);
	}
	if (argc > 2)
		rt_error_exit(data, "Too many arguments");
	path = argv[1];
	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	if (*filename == '\0')
		rt_error_exit(data, "Wrong argument: .rt file expected");
	extension = ft_strrchr(path, '.');
	if (!ft_streq(extension, ".rt") || ft_streq(filename, ".rt"))
		rt_error_exit(data, "Wrong argument: .rt file expected");
	data->path = path;
	data->title = filename;
}
