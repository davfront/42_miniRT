/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/07 15:58:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>

# include "key_linux.h"
# include "vec3.h"

# define WIN_WIDTH	(1024)
# define WIN_HEIGHT	(600)

# define BLACK		(0x00000000)
# define WHITE		(0x00FFFFFF)
# define RED		(0x00FF0000)
# define GREEN		(0x0000FF00)
# define BLUE		(0x000000FF)

typedef struct s_rgb {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_rgb;

typedef struct s_al {
	t_rgb	color;
	double	ratio;
}				t_al;

typedef struct s_cam {
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	up;
	t_float	fov;
	t_float	aspect_ratio;
	t_vec3	right;
	t_vec3	top;
}				t_cam;

typedef struct s_light {
	t_vec3	pos;
	t_rgb	color;
	double	ratio;
}				t_light;

typedef struct s_sphere {
	t_vec3	center;
	t_float	radius;
	t_rgb	color;
}				t_sphere;

typedef struct s_plane {
	t_vec3	point;
	t_vec3	normal;
	t_rgb	color;
}				t_plane;

typedef struct s_cylinder {
	t_vec3	center;
	t_vec3	axis;
	t_float	radius;
	t_float	height;
	t_rgb	color;
}				t_cylinder;

typedef struct s_ray {
	t_vec3	pos;
	t_vec3	dir;
}				t_ray;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
}		t_obj_type;

typedef struct s_obj {
	t_obj_type	type;
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}				t_obj;

typedef struct s_data {
	char		*path;
	char		*title;
	void		*mlx;
	void		*win;
	t_img		img;
	t_al		al;
	t_cam		cam;
	size_t		lights_size;
	t_light		*lights;
	size_t		objs_size;
	t_obj		*objs;
}				t_data;

// colors
t_rgb	rgb(unsigned char r, unsigned char g, unsigned char b);
t_rgb	rgb_by_int(int color);
int		rgb_to_int(t_rgb c);

// utils
void	rt_init(t_data *data);
void	rt_delete(t_data *data);
void	rt_error_exit(t_data *data, char *msg);

// parse
void	rt_parse(t_data *data);

// viewer
void	rt_viewer_start(t_data *data);
int		rt_viewer_render_frame(t_data *data);
void	rt_viewer_destroy(t_data *data);
void	rt_viewer_hooks(t_data *data);
int		rt_viewer_on_close(t_data *data);
void	rt_viewer_draw_pixel(t_data *data, int x, int y, int color);

// raytracer
t_ray	rt_get_view_ray(t_cam cam, int x, int y);
void	rt_draw_frame(t_data *data);

#endif
