/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 11:47:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_disc	disc(t_px center, unsigned int radius)
{
	t_disc	disc;

	disc.center = center;
	disc.radius = radius;
	return (disc);
}
