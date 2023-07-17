/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_help_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 14:56:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_help_label(t_data *data, int line, char *label)
{
	mlx_string_put(data->mlx, data->win, \
		24, HELP_OFFSET_Y + 20 * line, WHITE, label);
}
