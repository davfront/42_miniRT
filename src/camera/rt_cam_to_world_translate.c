/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world_translate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/24 00:00:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world_translate(t_mat4 c2w, t_vec3 d, t_float sensitivity)
{
	t_mat4	result;
	t_vec3	move;

	result = c2w;
	move = vec3_scale(d, -sensitivity);
	result = mat4_translate(result, move);
	return (result);
}
