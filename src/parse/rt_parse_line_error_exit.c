/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_line_error_exit.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 22:05:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_line_error_exit(t_data *data, char *msg)
{
	ft_putstr_fd("Error: parsing", STDERR_FILENO);
	if (data && data->line_index)
	{
		ft_putstr_fd(" line ", STDERR_FILENO);
		ft_putnbr_fd(data->line_index, STDERR_FILENO);
	}
	if (msg && *msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	rt_exit(data);
}
