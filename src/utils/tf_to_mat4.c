/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tf_to_mat4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/15 14:47:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	tf_to_mat4(t_tf tf)
{
	t_mat4	result;

	result = mat4_identity();
	result = mat4_scale(result, tf.scale);
	result = mat4_multiply_rev(result, mat4_from_quat(tf.rotate));
	result = mat4_translate(result, tf.move);
	return (result);
}
