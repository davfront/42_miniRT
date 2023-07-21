/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_texture_error_exit.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/21 01:11:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_texture_error_exit(t_data *data, char *line_type, char *value)
{
	if (value && ft_strncmp(value, "chess:", 6) == 0)
		rt_parse_value_error_exit(data, line_type, \
			"chessboard texture configuration", value);
	else
		rt_parse_value_error_exit(data, line_type, "color", value);
}
