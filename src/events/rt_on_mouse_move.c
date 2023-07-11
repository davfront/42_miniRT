/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_mouse_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 10:56:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_get_pointed_cs_helper_hovered(t_px p, t_cs cs)
{
	int		i;
	int		helper_id;
	t_px	hp;

	i = CS_SIZE - 1;
	while (i >= 0)
	{
		helper_id = cs.ordered_helper_types[i];
		hp = cs.helper_px[helper_id];
		if (pow(p.x - hp.x, 2) + pow(p.y - hp.y, 2) <= pow(CS_POINT_RAD, 2))
			return (helper_id);
		i--;
	}
	return (-1);
}

static void	rt_update_cs_helper_hovered(t_data *data, t_px p)
{
	if (!data)
		return ;
	if (data->ui.selected)
		data->ui.cs_helper_hovered = \
			rt_get_pointed_cs_helper_hovered(p, data->ui.cs);
	else
		data->ui.cs_helper_hovered = -1;
}

void	rt_on_mouse_move(t_data *data)
{
	rt_update_cs_helper_hovered(data, data->ui.mouse);
}
