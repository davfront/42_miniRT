/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_help_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 14:56:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_help_info(t_data *data, int line, char *label, char *value)
{
	rt_help_label(data, line, label);
	rt_help_value(data, line, value, WHITE);
}
