/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 17:02:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_obj_cylinder(char **strs, t_obj *obj_p)
{
	t_obj	obj;

	if (!obj_p || !strs || rt_strs_len(strs) != 5)
		return (0);
	obj.type = CYLINDER;
	if (!rt_parse_vec3(strs[0], &obj.cylinder.center))
		return (0);
	if (!rt_parse_vec3_dir(strs[1], &obj.cylinder.axis))
		return (0);
	if (!rt_parse_float_len(strs[2], &obj.cylinder.radius))
		return (0);
	obj.sphere.radius /= 2;
	if (!rt_parse_float_len(strs[3], &obj.cylinder.height))
		return (0);
	if (!rt_parse_rgb(strs[4], &obj.cylinder.color))
		return (0);
	*obj_p = obj;
	return (1);
}
