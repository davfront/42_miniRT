/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_delete_obj_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:11:29 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/25 10:11:34 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_delete_obj_lst_img(t_data *data, t_obj *obj)
{
	if (obj->tex_type == XPM && obj->xpm.img)
		mlx_destroy_image(data->mlx, obj->xpm.img);
}

void	rt_delete_obj_lst(t_data *data, t_list **lst)
{
	t_list	*tmp;

	if (!lst || !data)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		rt_delete_obj_lst_img(data, (*lst)->content);
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
