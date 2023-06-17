/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:09 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 15:48:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_streq(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (s1 == s2);
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}
