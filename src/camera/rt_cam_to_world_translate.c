/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_to_world_translate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 12:12:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	rt_cam_to_world_translate(t_mat4 c2w, t_vec3 d, t_float sensitivity)
{
	t_mat4	result;
	t_mat4	translation;
	t_vec3	v;

	result = c2w;
	v = vec3_scale(d, -sensitivity);
	translation = mat4_translate(mat4_identity(), v);
	result = mat4_multiply_rev(translation, result);
	return (result);
}
