/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:10:57 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/08 21:33:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef float	t_float;

typedef struct s_vec3 {
	t_float	x;
	t_float	y;
	t_float	z;
}				t_vec3;

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

#endif
