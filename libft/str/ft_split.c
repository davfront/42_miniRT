/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:48:39 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 17:04:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char const *set, char c)
{
	return (ft_strchr(set, c) != NULL);
}

static size_t	count_strs(char const *s, char const *set)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(set, s[i]) && (i == 0 || is_sep(set, s[i - 1])))
			n++;
		i++;
	}
	return (n);
}

static char	*get_str(char const *s, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && !is_sep(set, s[len]))
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	set_strs(char **strs, char const *s, char const *set)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(set, s[i]) && (i == 0 || is_sep(set, s[i - 1])))
		{
			strs[n] = get_str(s + i, set);
			if (!strs[n])
			{
				ft_free_split(strs);
				return (0);
			}
			n++;
		}
		i++;
	}
	strs[n] = NULL;
	return (1);
}

char	**ft_split(char const *s, char const *set)
{
	char	**strs;
	size_t	len;

	if (!s || !set || !*set)
		return (NULL);
	len = count_strs(s, set);
	strs = (char **)malloc((len + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	if (!set_strs(strs, s, set))
		return (NULL);
	return (strs);
}
