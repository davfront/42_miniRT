/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 14:56:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (msg && *msg)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		perror(NULL);
}
