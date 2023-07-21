/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:24:08 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/21 00:23:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vec3.h"

typedef struct s_al {
	t_rgb	color;
	t_float	ratio;
	t_rgb	computed;
}				t_al;

typedef struct s_cam {
	t_vec3			pos;
	t_vec3			dir;
	unsigned int	fov;
	t_float			tan_half_fov;
	t_float			aspect_ratio;
	t_mat4			c2w_temp;
	t_mat4			c2w;
	t_mat4			w2c;
}				t_cam;

typedef struct s_light {
	t_vec3	pos;
	t_rgb	color;
	t_float	ratio;
}				t_light;

typedef struct s_sphere {
	t_vec3	center;
	t_float	radius;
}				t_sphere;

typedef struct s_plane {
	t_vec3	point;
	t_vec3	normal;
}				t_plane;

typedef struct s_cylinder {
	t_vec3	center;
	t_vec3	axis;
	t_float	radius;
	t_float	height;
}				t_cylinder;

typedef struct s_cone {
	t_vec3	center;
	t_vec3	axis;
	t_float	radius;
	t_float	height;
}				t_cone;

typedef struct s_disc3 {
	t_vec3	center;
	t_vec3	axis;
	t_float	radius;
}				t_disc3;

typedef enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}		t_obj_type;

typedef struct s_tf {
	t_vec3		move;
	t_quat		rotate;
	t_vec3		scale;
}				t_tf;

typedef struct s_vec2 {
	t_float	x;
	t_float	y;
}				t_vec2;

typedef struct s_chess {
	t_rgb	color1;
	t_rgb	color2;
	t_vec2	size;
}				t_chess;

typedef enum e_tex_type {
	COLOR,
	CHESS
}		t_tex_type;

typedef struct s_obj {
	t_obj_type	type;
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	};
	t_tex_type	tex_type;
	union {
		t_rgb		color;
		t_chess		chess;
	};
	t_tf		tf;
	t_tf		tf_down;
}				t_obj;

#endif
