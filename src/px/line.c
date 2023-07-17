/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:04:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 13:11:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_line	line(t_px p1, t_px p2, unsigned int thickness)
{
	t_line	line;

	line.p1 = p1;
	line.p2 = p2;
	line.thickness = thickness;
	return (line);
}
