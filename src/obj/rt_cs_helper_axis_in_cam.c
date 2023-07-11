/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cs_helper_axis_in_cam.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 14:48:06 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_cs_helper_axis_in_cam(t_cs cs, int helper_id)
{
	if (helper_id == CS_MOV_X || helper_id == CS_ROT_X)
		return (cs.dx);
	if (helper_id == CS_MOV_Y || helper_id == CS_ROT_Y)
		return (cs.dy);
	if (helper_id == CS_MOV_Z || helper_id == CS_ROT_Z)
		return (cs.dz);
	return (vec3(0, 0, 0));
}
