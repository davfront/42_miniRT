/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 16:39:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_obj_plane(char **strs, t_obj *obj_p)
{
	t_obj	obj;

	if (!obj_p || !strs || rt_strs_len(strs) != 3)
		return (0);
	obj.type = PLANE;
	if (!rt_parse_vec3(strs[0], &obj.plane.point))
		return (0);
	if (!rt_parse_vec3_dir(strs[1], &obj.plane.normal))
		return (0);
	if (!rt_parse_rgb(strs[2], &obj.plane.color))
		return (0);
	*obj_p = obj;
	return (1);
}
