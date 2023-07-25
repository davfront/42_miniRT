/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 00:14:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_parse_material_is_str_valid(char *s)
{
	int		n;
	char	*sep;

	if (!s[0])
		return (0);
	n = 1;
	sep = ft_strchr(s, ',');
	while (sep)
	{
		n++;
		if (n > 5 || !sep[1] || sep[1] == ',')
			return (0);
		sep = ft_strchr(sep + 1, ',');
	}
	return (n == 5);
}

static void	rt_set_default_material(t_mtl *mtl)
{
	mtl->ka = DEFAULT_MTL_KA;
	mtl->kd = DEFAULT_MTL_KD;
	mtl->ks = DEFAULT_MTL_KS;
	mtl->ns = DEFAULT_MTL_NS;
	mtl->kr = DEFAULT_MTL_KR;
}

int	rt_parse_material_values(char **args, t_mtl *mtl)
{
	if (!mtl || !args)
		return (0);
	if (!rt_parse_float_ratio(args[0], &mtl->ka))
		return (0);
	if (!rt_parse_float_ratio(args[1], &mtl->kd))
		return (0);
	if (!rt_parse_float_ratio(args[2], &mtl->ks))
		return (0);
	if (!rt_parse_float(args[3], &mtl->ns) || mtl->ns < 0)
		return (0);
	if (!rt_parse_float_ratio(args[4], &mtl->kr))
		return (0);
	return (1);
}

int	rt_parse_material(char *s, t_mtl *mtl_p)
{
	char	**args;
	t_mtl	mtl;

	if (!mtl_p)
		return (0);
	if (!s)
		return (rt_set_default_material(mtl_p), 1);
	if (!rt_parse_material_is_str_valid(s))
		return (0);
	args = ft_split(s, ",");
	if (!args)
		return (rt_error("rt_parse_material: split failed\n"), 0);
	if (!rt_parse_material_values(args, &mtl))
		return (ft_free_split(&args), 0);
	*mtl_p = mtl;
	return (ft_free_split(&args), 1);
}
