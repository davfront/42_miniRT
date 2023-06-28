/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cam_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:32:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/23 16:17:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	rt_cam_right(t_mat4 c2w)
{
	return (mat4_multiply_axis(c2w, vec3(1, 0, 0)));
}

t_vec3	rt_cam_top(t_mat4 c2w)
{
	return (mat4_multiply_axis(c2w, vec3(0, 1, 0)));
}

t_vec3	rt_cam_forward(t_mat4 c2w)
{
	return (mat4_multiply_axis(c2w, vec3(0, 0, 1)));
}

t_vec3	rt_cam_dir(t_mat4 c2w)
{
	return (mat4_multiply_axis(c2w, vec3(0, 0, -1)));
}

t_vec3	rt_cam_pos(t_mat4 c2w)
{
	return (mat4_multiply_vec3(c2w, vec3(0, 0, 0)));
}
