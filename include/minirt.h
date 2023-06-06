/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/06 15:17:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "key_linux.h"

# define WIN_WIDTH	(1024)
# define WIN_HEIGHT	(600)

# define BLACK		(0x00000000)
# define WHITE		(0x00FFFFFF)
# define RED		(0x00FF0000)
# define GREEN		(0x0000FF00)
# define BLUE		(0x000000FF)

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_data {
	char		*path;
	char		*title;
	void		*mlx;
	void		*win;
	t_img		img;
}				t_data;

// utils
void	rt_free_all(t_data *data);
void	rt_error_exit(char *msg);

// draw
void	rt_draw_pixel(t_data *data, int x, int y, int color);
void	rt_draw_frame(t_data *data);

// viewer
void	rt_viewer_start(t_data *data);
int		rt_viewer_render_frame(t_data *data);
void	rt_viewer_destroy(t_data *data);
void	rt_viewer_hooks(t_data *data);
int		rt_viewer_on_close(t_data *data);

#endif
