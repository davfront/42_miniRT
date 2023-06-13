/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:57:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 14:27:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_uint(char *s, unsigned int *n)
{
	size_t			i;
	unsigned int	res;

	if (!s || !*s || !n)
		return (0);
	if (s[0] == '0' && s[1])
		return (0);
	i = 0;
	res = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		if (res > (UINT_MAX - (s[i] - '0')) / 10)
			return (0);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	*n = res;
	return (1);
}
