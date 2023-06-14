/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:10:57 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 09:18:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include <math.h>

typedef struct s_rgb {
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_rgb;

t_rgb			rgb(unsigned char r, unsigned char g, unsigned char b);
t_rgb			rgb_int(int color);
int				rgb_to_int(t_rgb c);
unsigned char	rgb_clamp(int x);
t_rgb			rgb_add(t_rgb c1, t_rgb c2);
t_rgb			rgb_subtract(t_rgb c1, t_rgb c2);
t_rgb			rgb_multiply(t_rgb c1, t_rgb c2);
t_rgb			rgb_scale(t_rgb c, float ratio);
t_rgb			rgb_mix(t_rgb c1, t_rgb c2, float ratio);

#endif
