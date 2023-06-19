/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:24:08 by atchougo          #+#    #+#             */
/*   Updated: 2023/06/13 14:57:16 by dapereir         ###   ########.fr       */
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
	t_float	ratio;
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

#endif
