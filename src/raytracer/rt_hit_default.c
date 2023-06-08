/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 15:56:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_hit_default(void)
{
	t_hit	hit;

	hit.obj = NULL;
	hit.color = rgb(0, 0, 0);
	hit.dist = INFINITY;
	hit.pos = vec3(0, 0, 0);
	hit.normal = vec3(0, 0, 0);
	return (hit);
}
