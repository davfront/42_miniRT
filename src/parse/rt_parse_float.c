/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:57:32 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:52:01 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_is_atof_valid(char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '-' && ft_isdigit(s[i + 1]))
		i++;
	if (s[i] == '0' && ft_isdigit(s[i + 1]))
		return (0);
	if (ft_streq(s, "-0"))
		return (0);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] == '.' && ft_isdigit(s[i + 1]))
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

static t_float	rt_atof_uint(char *s)
{
	t_float	res;
	size_t	i;

	if (!s || !*s)
		return (0);
	res = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res);
}

int	rt_parse_float(char *s, t_float *f)
{
	int		is_negative;
	t_float	int_part;
	t_float	dec_part;
	char	*dot_str;

	if (!rt_is_atof_valid(s))
		return (0);
	is_negative = (s[0] == '-');
	int_part = rt_atof_uint(s + is_negative);
	dec_part = 0;
	dot_str = ft_strchr(s, '.');
	if (dot_str)
		dec_part = rt_atof_uint(dot_str + 1) / pow(10, ft_strlen(dot_str + 1));
	*f = (int_part + dec_part) * (1 - 2 * is_negative);
	return (1);
}

int	rt_parse_float_len(char *s, t_float *len)
{
	t_float	f;

	if (!rt_parse_float(s, &f))
		return (0);
	if (f < 0)
		return (0);
	*len = f;
	return (1);
}

int	rt_parse_float_ratio(char *s, t_float *ratio)
{
	t_float	f;

	if (!rt_parse_float(s, &f))
		return (0);
	if (f < 0 || f > 1)
		return (0);
	*ratio = f;
	return (1);
}
