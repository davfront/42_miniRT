/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:19:30 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/27 16:14:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_ftoa_prepend_minus(char **s)
{
	char	*temp;

	temp = ft_strjoin("-", *s);
	ft_free((void **)s);
	*s = temp;
}

static char	*rt_ftoa_dec_str(float dec_part, int precision)
{
	char	*dec_str;
	char	*str;
	int		i;

	str = ft_calloc(precision + 2, sizeof(char));
	str[0] = '.';
	i = 0;
	dec_part *= 10;
	while (dec_part < 1 && i < precision)
	{
		i++;
		str[i] = '0';
		dec_part *= 10;
	}
	if (i < precision)
	{
		dec_part *= pow(10, precision - i - 1);
		dec_part = (int)dec_part;
		dec_str = ft_itoa(dec_part);
	}
	else
		dec_str = ft_calloc(1, sizeof(char));
	ft_strlcpy(str + i + 1, dec_str, precision - i + 1);
	ft_free((void **)&dec_str);
	return (str);
}

char	*rt_ftoa(float f, int precision)
{
	char	*int_str;
	char	*dec_str;
	char	*str;
	int		int_part;
	float	dec_part;

	int_part = (int)f;
	int_str = ft_itoa(int_part);
	dec_part = (f - (float)int_part) * (1 - 2 * (f < 0));
	if (dec_part > 0 && int_part == 0)
		rt_ftoa_prepend_minus(&int_str);
	if (precision > 0)
	{
		dec_str = rt_ftoa_dec_str(dec_part, precision);
		str = ft_strjoin(int_str, dec_str);
		ft_free((void **)&int_str);
		ft_free((void **)&dec_str);
		return (str);
	}
	return (int_str);
}
