/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 23:02:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_free_buffer(t_data *data)
{
	size_t	i;

	if (!data || !data->rdr.buf)
		return ;
	i = 0;
	while (i < WIN_WIDTH)
	{
		ft_free((void **)&(data->rdr.buf[i]));
		i++;
	}
	ft_free((void **)&(data->rdr.buf));
}

void	rt_delete(t_data *data)
{
	if (!data)
		return ;
	if (data->fd != -1)
	{
		ft_free_gnl(data->fd);
		close(data->fd);
		data->fd = -1;
	}
	ft_free((void **)&(data->line));
	ft_free_split(&data->strs);
	ft_free((void **)&(data->al));
	ft_free((void **)&(data->cam));
	ft_lstclear(&data->light_lst, free);
	ft_lstclear(&data->obj_lst, free);
	rt_viewer_destroy(data);
	rt_free_buffer(data);
}
