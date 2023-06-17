/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_write.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:50:08 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/27 17:59:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_WRITE_H
# define LIBFT_WRITE_H

# include <unistd.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putendl(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);

#endif