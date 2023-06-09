/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:55:14 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/09 17:05:50 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _DEBUG_H_
# define _DEBUG_H_

# define BLACK_P  "\033[0;30m"
# define RED_P    "\033[0;31m"
# define GREEN_P  "\033[0;32m"
# define YELLOW_P "\033[0;33m"
# define BLUE_P   "\033[0;34m"
# define PURPLE_P "\033[0;35m"
# define CYAN_P   "\033[0;36m"
# define WHITE_P  "\033[0;37m"
# define RESET_P  "\033[0m"
# define DELETE_P printf("\033M\033[2K");

# define DEBUG(x, ...) printf(CYAN_P"[%s]"GREEN_P"[%s:%d] "YELLOW_P x RESET_P"\n",\
							__FILE__, __FUNCTION__ ,__LINE__, ##__VA_ARGS__);

#endif /* _DEBUG_H_ */
