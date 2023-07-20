/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_chess_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/20 16:34:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_get_chess_color(t_vec2 p, t_chess chess)
{
	int	tile_index;

	tile_index = (int)(p.x / chess.size.x) + (int)(p.y / chess.size.y);
	tile_index -= (p.x < 0) + (p.y < 0);
	if (tile_index % 2)
		return (chess.color1);
	else
		return (chess.color2);
}
