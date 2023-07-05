/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 23:01:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_alloc_buffer(t_data *data)
{
	size_t	i;

	if (!data)
		return ;
	data->rdr.buf = ft_calloc(WIN_WIDTH, sizeof(t_buf *));
	i = 0;
	while (i < WIN_WIDTH)
	{
		data->rdr.buf[i] = ft_calloc(WIN_HEIGHT, sizeof(t_buf));
		i++;
	}
}

void	rt_init(t_data *data)
{
	if (!data)
		return ;
	ft_bzero(data, sizeof(t_data));
	data->fd = -1;
	rt_alloc_buffer(data);
}
