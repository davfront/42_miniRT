/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_hit_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:01:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 14:14:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	rt_hit_default(void)
{
	t_hit	hit;

	hit.obj = NULL;
	hit.color = rgb(0, 0, 0);
	hit.dist = -1;
	hit.pos = vec3(0, 0, 0);
	hit.normal = vec3(0, 0, 0);
	return (hit);
}
