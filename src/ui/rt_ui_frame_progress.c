/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ui_frame_progress.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:16:53 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 14:47:44 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_ui_frame_progress(t_data *data)
{
	int		padding;
	t_rect	rect;

	if (!data || data->rdr.step > data->rdr.step_max)
		return ;
	padding = 2;
	rect.p = px(padding, padding);
	rect.h = 2;
	rect.w = 0;
	if (data->rdr.step_max)
		rect.w = (t_float)(WIN_WIDTH - 2 * padding) \
			* data->rdr.step / data->rdr.step_max;
	rt_draw_rect(data, rect, rgb(255, 255, 255), 1);
}
