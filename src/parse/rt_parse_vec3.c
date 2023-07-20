/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_vec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:15:04 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/20 11:24:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_split_vec3_str(char *s, char **xs, char **ys, char **zs)
{
	char	*sep;

	if (!s || !*s)
		return (0);
	*xs = s;
	sep = ft_strchr(*xs, ',');
	if (!sep || sep == *xs || !sep[1])
		return (0);
	sep[0] = '\0';
	*ys = sep + 1;
	sep = ft_strchr(*ys, ',');
	if (!sep || sep == *ys || !sep[1])
		return (0);
	sep[0] = '\0';
	*zs = sep + 1;
	return (1);
}

int	rt_parse_vec3(char *s, t_vec3 *v)
{
	char	*s2;
	char	*cs[3];
	t_float	cf[3];

	if (!s || !*s || !v)
		return (0);
	s2 = ft_strdup(s);
	if (!s2)
		return (rt_error("rt_parse_vec3: alloc failed\n"), 0);
	if (!rt_split_vec3_str(s2, &cs[0], &cs[1], &cs[2]))
		return (ft_free((void **)&s2), 0);
	if (!rt_parse_float(cs[0], &cf[0])
		|| !rt_parse_float(cs[1], &cf[1])
		|| !rt_parse_float(cs[2], &cf[2])
	)
		return (ft_free((void **)&s2), 0);
	*v = vec3(cf[0], cf[1], cf[2]);
	return (ft_free((void **)&s2), 1);
}

int	rt_parse_vec3_dir(char *s, t_vec3 *dir)
{
	t_vec3	v;

	if (!rt_parse_vec3(s, &v))
		return (0);
	if (v.x < -1 || v.x > 1)
		return (0);
	if (v.y < -1 || v.y > 1)
		return (0);
	if (v.z < -1 || v.z > 1)
		return (0);
	if (!vec3_length_squared(v))
		return (0);
	*dir = vec3_normalize(v);
	return (1);
}
