/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:10:57 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/26 13:57:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <libft.h>

typedef float	t_float;

typedef struct s_vec3 {
	t_float	x;
	t_float	y;
	t_float	z;
}				t_vec3;

typedef struct s_mat4 {
	t_float	m[4][4];
}				t_mat4;

typedef struct s_quat {
	t_float	w;
	t_float	x;
	t_float	y;
	t_float	z;
}				t_quat;

t_vec3	vec3(t_float x, t_float y, t_float z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_multiply(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, t_float f);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_reflect(t_vec3 v, t_vec3 n);
t_float	vec3_dot(t_vec3 a, t_vec3 b);
t_float	vec3_length(t_vec3 v);
t_float	vec3_length_squared(t_vec3 v);
int		vec3_equals(t_vec3 a, t_vec3 b);

t_quat	quat(t_float w, t_float x, t_float y, t_float z);
t_quat	quat_from_vec3(t_vec3 v0, t_vec3 v1);
t_quat	quat_multiply(t_quat a, t_quat b);
t_quat	quat_from_axis_angle(t_vec3 axis, t_float angle);

t_mat4	mat4_zero(void);
t_mat4	mat4_identity(void);
t_mat4	mat4_translate(t_mat4 m, t_vec3 v);
t_mat4	mat4_scale(t_mat4 m, t_float f);
t_mat4	mat4_rotate_x(t_mat4 m, t_float a);
t_mat4	mat4_rotate_y(t_mat4 m, t_float a);
t_mat4	mat4_rotate_z(t_mat4 m, t_float a);
t_mat4	mat4_rotate_axis(t_mat4 m, t_vec3 axis, float_t angle);
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);
t_mat4	mat4_multiply_rev(t_mat4 a, t_mat4 b);
t_mat4	mat4_from_quat(t_quat q);

t_vec3	mat4_multiply_vec3(t_mat4 m, t_vec3 v);
t_vec3	mat4_multiply_axis(t_mat4 m, t_vec3 v);

#endif
