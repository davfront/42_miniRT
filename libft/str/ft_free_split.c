/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:48:39 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/15 00:15:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***strs_p)
{
	size_t	i;

	if (!strs_p || !*strs_p)
		return ;
	i = 0;
	while ((*strs_p)[i])
	{
		ft_free((void **)(&(*strs_p)[i]));
		i++;
	}
	ft_free((void **)strs_p);
}
