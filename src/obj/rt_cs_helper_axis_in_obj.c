/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cs_helper_axis_in_obj.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 14:50:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_cs_helper_axis_in_obj(int helper_id)
{
	if (helper_id == CS_MOV_X || helper_id == CS_ROT_X)
		return (vec3(0, 0, 1));
	if (helper_id == CS_MOV_Y || helper_id == CS_ROT_Y)
		return (vec3(0, 1, 0));
	if (helper_id == CS_MOV_Z || helper_id == CS_ROT_Z)
		return (vec3(-1, 0, 0));
	return (vec3(0, 0, 0));
}
