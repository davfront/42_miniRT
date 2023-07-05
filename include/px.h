/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/05 13:12:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_H
# define PX_H

typedef struct s_px {
	int	x;
	int	y;
}				t_px;

typedef struct s_line {
	t_px			p1;
	t_px			p2;
	unsigned int	thickness;
}				t_line;

typedef struct s_disc {
	t_px			center;
	unsigned int	radius;
}				t_disc;

typedef struct s_rect {
	t_px			p;
	unsigned int	w;
	unsigned int	h;
}				t_rect;

t_px			px(int x, int y);
t_line			line(t_px p1, t_px p2, unsigned int thickness);
t_disc			disc(t_px center, unsigned int radius);
t_rect			rect(t_px p, unsigned int w, unsigned int h);

#endif
