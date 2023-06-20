/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/16 11:48:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	ft_lstclear(&data->vertex_lst, free);
	ft_lstclear(&data->obj_lst, free);
	rt_viewer_destroy(data);
}
