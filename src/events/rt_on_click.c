/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_on_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/11 10:59:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_on_click(t_data *data)
{
	t_px	p;

	if (!data)
		return ;
	p = data->ui.mouse;
	if (data->ui.selected == data->rdr.buf[p.x][p.y].obj)
		data->ui.selected = NULL;
	else
		data->ui.selected = data->rdr.buf[p.x][p.y].obj;
}
