/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world_translate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 17:27:14 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world_translate(t_mat4 c2w, t_float dx, t_float dy, \
	t_float sensitivity)
{
	t_mat4	result;
	t_float	len_x;
	t_float	len_y;
	t_vec3	move;

	result = c2w;
	len_x = dx * sensitivity;
	len_y = dy * sensitivity;
	move = vec3(-len_x, -len_y, 0);
	result = mat4_translate(result, move);
	return (result);
}
