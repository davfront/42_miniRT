/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 18:42:16 by atchougo         ###   ########.fr       */
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
# include "rgb.h"
# include "vec3.h"
# include "scene.h"
# include "debug.h" // TODO : delete debug.h before correction

# define WIN_WIDTH	(1024)
# define WIN_HEIGHT	(600)

# define PHONG_DIFFUSE_WEIGHT		(0.6)
# define PHONG_SPECULAR_WEIGHT		(0.4)
# define PHONG_SPECULAR_EXPONENT	(50)

typedef struct s_hit {
	t_obj	*obj;
	t_rgb	color;
	t_float	dist;
	t_vec3	pos;
	t_vec3	normal;
}				t_hit;

typedef struct s_ray {
	t_vec3	pos;
	t_vec3	dir;
	t_hit	hit;
}				t_ray;

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
	t_al		al;
	t_cam		cam;
	size_t		lights_size;
	t_light		*lights;
	size_t		objs_size;
	t_obj		*objs;
}				t_data;

// utils
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
void	rt_viewer_draw_pixel(t_data *data, int x, int y, t_rgb color);

// raytracer
t_ray	rt_get_view_ray(t_cam cam, int x, int y);
void	rt_draw_frame(t_data *data);
t_hit	rt_hit_default(void);
t_hit	rt_get_sphere_hit(t_ray ray, t_obj *obj);
t_hit	rt_get_plane_hit(t_ray ray, t_obj *obj);
t_hit	rt_get_obj_hit(t_ray ray, t_obj *obj);
t_hit	rt_get_closest_hit(t_data *data, t_ray ray);
t_rgb	rt_get_hit_color(t_data *data, t_ray ray);

#endif
