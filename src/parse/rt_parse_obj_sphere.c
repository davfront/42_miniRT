/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/13 17:02:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_parse_obj_sphere(char **strs, t_obj *obj_p)
{
	t_obj	obj;

	if (!obj_p || !strs || rt_strs_len(strs) != 3)
		return (0);
	obj.type = SPHERE;
	if (!rt_parse_vec3(strs[0], &obj.sphere.center))
		return (0);
	if (!rt_parse_float_len(strs[1], &obj.sphere.radius))
		return (0);
	obj.sphere.radius /= 2;
	if (!rt_parse_rgb(strs[2], &obj.sphere.color))
		return (0);
	*obj_p = obj;
	return (1);
}
