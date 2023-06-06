/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/07 00:16:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_error_exit(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(NULL);
	rt_delete(data);
	exit(EXIT_FAILURE);
}
