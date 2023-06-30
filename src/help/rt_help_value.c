/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_help_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 14:56:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_help_value(t_data *data, int line, char *value, int color)
{
	if (!value)
		return ;
	mlx_string_put(data->mlx, data->win, \
		HELP_VALUE_X, HELP_OFFSET_Y + 20 * line, color, value);
}

void	rt_help_value_i(t_data *data, int line, int i, int color)
{
	char	*s;

	s = ft_itoa(i);
	rt_help_value(data, line, s, color);
	ft_free((void **)&s);
}

void	rt_help_value_f(t_data *data, int line, float f, int color)
{
	char	*s;

	s = rt_ftoa(f, 1);
	rt_help_value(data, line, s, color);
	ft_free((void **)&s);
}

void	rt_help_value_perc(t_data *data, int line, float f, int color)
{
	char	*s;

	s = rt_ftoa(f, 1);
	s[ft_strlen(s) - 2] = '%';
	s[ft_strlen(s) - 1] = '\0';
	rt_help_value(data, line, s, color);
	ft_free((void **)&s);
}
