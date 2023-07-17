/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/30 15:22:25 by dapereir         ###   ########.fr       */
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
# include <pthread.h>
# include <sys/time.h>

# include "key_linux.h"
# include "rgb.h"
# include "vec3.h"
# include "scene.h"
# include "debug.h" // TODO : delete debug.h before correction

# define WIN_WIDTH	(1024)
# define WIN_HEIGHT	(600)

# define T_MIN	(0.001)

# define PHONG_DIFFUSE_WEIGHT		(0.6)
# define PHONG_SPECULAR_WEIGHT		(0.4)
# define PHONG_SPECULAR_EXPONENT	(50)

# define ENABLE_THREAD	1
# define THREAD_NB		4

# define LOW_RES_ENABLED	1

# define HELP_OFFSET_Y	(20)
# define HELP_VALUE_X	(160)
# define HELP_WIDTH		(250)

# define BLACK		(0x00000000)
# define WHITE		(0x00FFFFFF)
# define RED		(0x00FF0000)
# define GREEN		(0x0000FF00)
# define BLUE		(0x000000FF)

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

typedef struct s_ui {
	int	changed;
	int	mouse_x0;
	int	mouse_y0;
	int	mouse_dx;
	int	mouse_dy;
	int	mouse_left_btn;
	int	mouse_right_btn;
	int	help;
}				t_ui;

typedef struct s_buf {
	int		done;
	t_rgb	color;
}				t_buf;

typedef struct s_data	t_data;

typedef struct s_thread {
	int			id;
	pthread_t	thread;
	t_data		*data;
}				t_thread;

typedef struct s_rdr {
	t_thread	thread[THREAD_NB];
	t_buf		buf[WIN_WIDTH][WIN_HEIGHT];
	int			tile_size;
	int			step_max;
	int			step;
	t_float		fps;
}				t_rdr;

typedef struct s_data {
	char		*path;
	char		*title;
	int			fd;
	char		*line;
	size_t		line_index;
	char		**strs;
	void		*mlx;
	void		*win;
	t_img		img;
	t_rdr		rdr;
	t_ui		ui;
	t_al		*al;
	t_cam		*cam;
	t_list		*light_lst;
	t_list		*obj_lst;
}				t_data;

// utils
void	rt_delete(t_data *data);
void	rt_error(char *msg);
void	rt_exit(t_data *data);
void	rt_error_exit(t_data *data, char *msg);
int		rt_strs_len(char **strs);
void	rt_set_fps(t_data *data, struct timeval start, struct timeval end);
char	*rt_ftoa(float f, int precision);

// parse
int		rt_parse_uint(char *s, unsigned int *n);
int		rt_parse_rgb(char *s, t_rgb *c);
int		rt_parse_float(char *s, t_float *f);
int		rt_parse_float_len(char *s, t_float *len);
int		rt_parse_float_ratio(char *s, t_float *ratio);
int		rt_parse_vec3(char *s, t_vec3 *v);
int		rt_parse_vec3_dir(char *s, t_vec3 *dir);
void	rt_parse_input(t_data *data, int argc, char **argv);
void	rt_parse_line(t_data *data);
void	rt_parse_ambient_light(t_data *data, char **strs);
void	rt_parse_camera(t_data *data, char **strs);
void	rt_parse_light(t_data *data, char **strs);
void	rt_parse_obj_plane(t_data *data, char **strs);
void	rt_parse_obj_sphere(t_data *data, char **strs);
void	rt_parse_obj_cylinder(t_data *data, char **strs);
void	rt_parse_line_error_exit(t_data *data, char *msg);
void	rt_parse_value_error_exit(t_data *data, char *line_type, char *label, \
	char *value);
void	rt_parse(t_data *data, int argc, char **argv);

// viewer
void	rt_viewer_start(t_data *data);
int		rt_viewer_render_frame(t_data *data);
void	rt_viewer_destroy(t_data *data);
void	rt_viewer_hooks(t_data *data);
int		rt_viewer_on_close(t_data *data);
int		rt_viewer_on_mouse_down(int button, int x, int y, t_data *data);
int		rt_viewer_on_mouse_up(int button, int x, int y, t_data *data);
int		rt_viewer_on_mouse_move(int x, int y, t_data *data);
int		rt_viewer_on_keydown(int keycode, t_data *data);
int		rt_viewer_on_keyup(int keycode, t_data *data);
void	rt_viewer_draw_pixel(t_data *data, int x, int y, t_rgb color);
void	rt_viewer_thread_handler(t_data *data);

// help
void	rt_help_label(t_data *data, int line, char *label);
void	rt_help_value(t_data *data, int line, char *value, int color);
void	rt_help_value_i(t_data *data, int line, int i, int color);
void	rt_help_value_f(t_data *data, int line, float f, int color);
void	rt_help_value_perc(t_data *data, int line, float f, int color);
void	rt_help_info(t_data *data, int line, char *label, char *value);
void	rt_help(t_data *data);

// raytracer
t_ray	rt_get_view_ray(t_cam cam, int x, int y);
void	rt_draw_frame(t_data *data);
int		rt_lowres_estimate_size(t_data *data);
void	rt_draw_frame_lowres(t_data *data);
void	*rt_draw_frame_thread(void *tv);
t_hit	rt_hit_default(void);
int		rt_get_sphere_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
int		rt_get_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
int		rt_get_obj_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
t_hit	rt_get_closest_hit(t_data *data, t_ray ray);
t_rgb	rt_get_hit_color(t_data *data, t_ray ray);

// camera
t_vec3	rt_cam_right(t_mat4 c2w);
t_vec3	rt_cam_top(t_mat4 c2w);
t_vec3	rt_cam_forward(t_mat4 c2w);
t_vec3	rt_cam_dir(t_mat4 c2w);
t_vec3	rt_cam_pos(t_mat4 c2w);
t_mat4	rt_cam_to_world(t_vec3 cam_pos, t_vec3 cam_dir);
t_mat4	rt_cam_to_world_translate(t_mat4 c2w, t_vec3 d, t_float sensitivity);
t_mat4	rt_cam_to_world_rotate(t_mat4 c2w, t_float dx, t_float dy, \
	t_float sensitivity);
t_mat4	rt_cam_projection(unsigned int fov);
void	rt_cam_update_fov(t_data *data, int delta_fov);
#endif
