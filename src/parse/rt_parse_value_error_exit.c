/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_value_error_exit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 22:48:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_value_error_exit(t_data *data, char *line_type, char *label, \
	char *value)
{
	ft_putstr_fd("Error: parsing", STDERR_FILENO);
	if (data && data->line_index)
	{
		ft_putstr_fd(" line ", STDERR_FILENO);
		ft_putnbr_fd(data->line_index, STDERR_FILENO);
	}
	if (line_type && *line_type)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(line_type, STDERR_FILENO);
	}
	if (label && value)
	{
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("` is not a valid ", STDERR_FILENO);
		ft_putstr_fd(label, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	rt_exit(data);
}
