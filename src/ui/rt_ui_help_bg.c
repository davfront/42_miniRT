/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ui_help_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:29:02 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 13:38:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_ui_help_bg(t_data *data)
{
	t_rect	rect;

	if (!data || !data->ui.help)
		return ;
	rect.p = px(0, 0);
	rect.w = HELP_WIDTH;
	rect.h = WIN_HEIGHT;
	rt_draw_rect(data, rect, rgb(0, 0, 0), 0.7);
}
