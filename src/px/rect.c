/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 11:46:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rect	rect(t_px p, unsigned int w, unsigned int h)
{
	t_rect	rect;

	rect.p = p;
	rect.w = w;
	rect.h = h;
	return (rect);
}
