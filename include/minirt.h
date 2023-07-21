/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/20 11:55:09 by dapereir         ###   ########.fr       */
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
# include "px.h"
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
# define HELP_VALUE_X	(180)
# define HELP_WIDTH		(250)

# define BLACK		(0x00000000)
# define WHITE		(0x00FFFFFF)
# define GRAY		(0x00999999)
# define RED		(0x00FF0000)
# define GREEN		(0x0000FF00)
# define BLUE		(0x000000FF)
# define YELLOW		(0x00FFFF00)

# define CS_POINT_RAD	(8)
# define CS_MOV_LEN		(100)
# define CS_ROT_LEN		(80)
# define CS_RED			(0x00eb6663)
# define CS_GREEN		(0x0071deb6)
# define CS_BLUE		(0x004b98f7)

enum e_cs_helper_type {
	CS_ORIG,
	CS_MOV_X,
	CS_MOV_Y,
	CS_MOV_Z,
	CS_ROT_X,
	CS_ROT_Y,
	CS_ROT_Z,
	CS_SIZE
};

typedef struct s_cs {
	t_vec3	center;
	t_vec3	dx;
	t_vec3	dy;
	t_vec3	dz;
	t_px	helper_px[CS_SIZE];
	int		ordered_helper_types[CS_SIZE];
}				t_cs;

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
	int		changed;
	t_px	mouse;
	t_px	mouse_down;
	t_px	mouse_dragged;
	int		mouse_left_btn;
	int		mouse_right_btn;
	int		help;
	t_obj	*selected;
	t_cs	cs_down;
	t_cs	cs;
	int		cs_helper_hovered;
	int		cs_helper_selected;
}				t_ui;

typedef struct s_buf {
	int		exact;
	t_rgb	color;
	t_obj	*obj;
}				t_buf;

typedef struct s_data	t_data;

typedef struct s_thread {
	int			id;
	pthread_t	thread;
	t_data		*data;
}				t_thread;

typedef struct s_rdr {
	t_thread	thread[THREAD_NB];
	t_buf		**buf;
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
void		rt_init(t_data *data);
void		rt_delete(t_data *data);
void		rt_error(char *msg);
void		rt_exit(t_data *data);
void		rt_error_exit(t_data *data, char *msg);
int			rt_strs_len(char **strs);
void		rt_set_fps(t_data *data, struct timeval start, struct timeval end);
char		*rt_ftoa(float f, int precision);
t_vec3		px_to_vec3(t_px p);
t_px		vec3_to_px(t_vec3 v);
t_mat4		tf_to_mat4(t_tf tf);

// parse
int			rt_parse_uint(char *s, unsigned int *n);
int			rt_parse_rgb(char *s, t_rgb *c);
int			rt_parse_float(char *s, t_float *f);
int			rt_parse_float_len(char *s, t_float *len);
int			rt_parse_float_ratio(char *s, t_float *ratio);
int			rt_parse_vec3(char *s, t_vec3 *v);
int			rt_parse_vec3_dir(char *s, t_vec3 *dir);
void		rt_parse_input(t_data *data, int argc, char **argv);
void		rt_parse_line(t_data *data);
void		rt_parse_ambient_light(t_data *data, char **strs);
void		rt_parse_camera(t_data *data, char **strs);
void		rt_parse_light(t_data *data, char **strs);
void		rt_parse_obj_plane(t_data *data, char **strs);
void		rt_parse_obj_sphere(t_data *data, char **strs);
void		rt_parse_obj_cylinder(t_data *data, char **strs);
void		rt_parse_obj_cone(t_data *data, char **strs);
void		rt_parse_line_error_exit(t_data *data, char *msg);
void		rt_parse_value_error_exit(t_data *data, char *line_type, \
				char *label, char *value);
void		rt_parse(t_data *data, int argc, char **argv);

// viewer
void		rt_viewer_start(t_data *data);
int			rt_viewer_render_frame(t_data *data);
void		rt_viewer_destroy(t_data *data);
void		rt_viewer_hooks(t_data *data);
int			rt_viewer_on_close(t_data *data);
int			rt_viewer_on_mouse_down(int button, int x, int y, t_data *data);
int			rt_viewer_on_mouse_up(int button, int x, int y, t_data *data);
int			rt_viewer_on_mouse_move(int x, int y, t_data *data);
int			rt_viewer_on_keydown(int keycode, t_data *data);
int			rt_viewer_on_keyup(int keycode, t_data *data);
t_rgb		rt_viewer_get_pixel(t_data *data, int x, int y);
void		rt_viewer_set_pixel(t_data *data, int x, int y, t_rgb color);
void		rt_viewer_thread_handler(t_data *data);

// events
void		rt_on_click(t_data *data);
void		rt_on_mouse_move(t_data *data);
void		rt_on_scroll(t_data *data, int is_up);
void		rt_on_dragstart(t_data *data);
void		rt_on_dragend(t_data *data);
void		rt_on_drag(t_data *data);
void		rt_on_right_dragstart(t_data *data);
void		rt_on_right_dragend(t_data *data);
void		rt_on_right_drag(t_data *data);
void		rt_on_drag_cs_helper(t_data *data, int helper_id);

// help
void		rt_help_label(t_data *data, int line, char *label);
void		rt_help_value(t_data *data, int line, char *value, int color);
void		rt_help_value_i(t_data *data, int line, int i, int color);
void		rt_help_value_f(t_data *data, int line, float f, int color);
void		rt_help_value_perc(t_data *data, int line, float f, int color);
void		rt_help_info(t_data *data, int line, char *label, char *value);
int			rt_help_obj(t_data *data, t_obj obj, int line);
void		rt_help(t_data *data);

// raytracer
t_ray		rt_get_view_ray(t_cam cam, int x, int y);
int			rt_lowres_estimate_size(t_data *data);
void		rt_lowres_draw_step(t_data *data, int step);
void		*rt_lowres_draw_step_thread(void *tv);
void		rt_draw_frame(t_data *data);
t_hit		rt_hit_default(void);
int			rt_get_sphere_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
int			rt_get_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
t_float		rt_get_disc_hit_dist(t_ray ray, t_disc3 disc, t_float t_max);
t_float		rt_get_cylinder_body_hit_dist(t_ray ray, t_cylinder cy, \
				t_float t_max);
int			rt_get_cylinder_hit(t_ray ray, t_obj *obj, t_float t_max, \
				t_hit *hit);
t_float		rt_get_cone_body_hit_dist(t_ray ray, t_cone co, t_float t_max);
int			rt_get_cone_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
int			rt_get_obj_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit);
t_hit		rt_get_closest_hit(t_data *data, t_ray ray);
t_rgb		rt_get_hit_color(t_data *data, t_ray ray);

// camera
t_vec3		rt_cam_right(t_mat4 c2w);
t_vec3		rt_cam_top(t_mat4 c2w);
t_vec3		rt_cam_forward(t_mat4 c2w);
t_vec3		rt_cam_dir(t_mat4 c2w);
t_vec3		rt_cam_pos(t_mat4 c2w);
t_mat4		rt_cam_to_world(t_vec3 cam_pos, t_vec3 cam_dir);
t_mat4		rt_cam_to_world_translate(t_mat4 c2w, t_vec3 d, \
				t_float sensitivity);
t_mat4		rt_cam_to_world_rotate(t_mat4 c2w, t_float dx, t_float dy, \
				t_float sensitivity);
t_vec3		rt_cam_ndc_to_camera_space(t_cam cam, t_vec3 ndc);
t_vec3		rt_cam_camera_space_to_ndc(t_cam cam, t_vec3 v);
void		rt_cam_update_fov(t_data *data, int delta_fov);
void		rt_cam_update_c2w(t_data *data, t_mat4 c2w);
t_px		rt_cam_c2s(t_data *data, t_vec3 v);
t_px		rt_cam_w2s(t_data *data, t_vec3 v);

// obj
t_tf		rt_get_sphere_transformations(t_sphere sp);
t_tf		rt_get_plane_transformations(t_plane pl);
t_tf		rt_get_cylinder_transformations(t_cylinder cy);
t_tf		rt_get_cone_transformations(t_cone co);
t_sphere	rt_get_transformed_sphere(t_obj obj);
t_plane		rt_get_transformed_plane(t_obj obj);
t_cylinder	rt_get_transformed_cylinder(t_obj obj);
t_cone		rt_get_transformed_cone(t_obj obj);
t_vec3		rt_cs_helper_axis_in_obj(int helper_id);
t_vec3		rt_cs_helper_axis_in_cam(t_cs cs, int helper_id);

// px_draw
void		rt_draw_px(t_data *data, t_px p, t_rgb color, float alpha);
void		rt_draw_line(t_data *data, t_line, t_rgb color);
void		rt_draw_line_px(t_data *data, t_line line, t_rgb color, \
				float alpha);
void		rt_draw_disc(t_data *data, t_disc, t_rgb color, float alpha);
void		rt_draw_rect(t_data *data, t_rect, t_rgb color, float alpha);
void		rt_draw_cs(t_data *data, t_cs cs);

// ui
void		rt_ui_help_bg(t_data *data);
void		rt_ui_frame_progress(t_data *data);
void		rt_ui_bounding_box(t_data *data, t_obj *obj);
void		rt_ui_selected(t_data *data);

#endif
