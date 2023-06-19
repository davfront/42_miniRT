/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:15:04 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/19 14:23:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_split_rgb_str(char *s, char **rs, char **gs, char **bs)
{
	char	*sep;

	if (!s || !*s)
		return (0);
	*rs = s;
	sep = ft_strchr(*rs, ',');
	if (!sep || sep == *rs || !sep[1])
		return (0);
	sep[0] = '\0';
	*gs = sep + 1;
	sep = ft_strchr(*gs, ',');
	if (!sep || sep == *gs || !sep[1])
		return (0);
	sep[0] = '\0';
	*bs = sep + 1;
	return (1);
}

int	rt_parse_rgb(char *s, t_rgb *c)
{
	size_t			len;
	char			*cs[3];
	unsigned int	ci[3];

	if (!s || !c)
		return (0);
	len = ft_strlen(s);
	if (len < 5 || len > 11)
		return (0);
	if (!rt_split_rgb_str(s, &cs[0], &cs[1], &cs[2]))
		return (0);
	if (!rt_parse_uint(cs[0], &ci[0]) || ci[0] > 255
		|| !rt_parse_uint(cs[1], &ci[1]) || ci[1] > 255
		|| !rt_parse_uint(cs[2], &ci[2]) || ci[2] > 255
	)
		return (0);
	*c = rgb(ci[0], ci[1], ci[2]);
	return (1);
}
