/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_plane_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:19:54 by atchougo          #+#    #+#             */
/*   Updated: 2023/07/20 08:20:40 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_rgb	rt_plane_get_pixel(t_img img, int x, int y)
// {
// 	char	*dst;
// 	int		color_int;

// 	if (x < 0 || x > WIN_WIDTH - 1)
// 		return (rgb(0, 0, 0));
// 	if (y < 0 || y > WIN_HEIGHT - 1)
// 		return (rgb(0, 0, 0));
// 	dst = img.addr;
// 	dst += y * img.len;
// 	dst += x * (img.bpp / 8);
// 	color_int = *(unsigned int *)dst;
// 	return (rgb_int(color_int));
// }

// static t_rgb calcul_color(t_obj *obj, t_vec3 pos)
// {
// 	t_vec3	e1 = vec3_normalize(vec3_cross(obj->plane.normal,obj->plane.point));
// 	t_vec3	e2 = vec3_normalize(vec3_cross(obj->plane.normal,e1));
// 	// pos = vec3_normalize(pos);
// 	t_float	u = vec3_dot(e1, pos);
// 	t_float	v = vec3_dot(e2, pos);
// 	// t_float	u = (atan2f(pos.z, pos.x) + M_PI) / ((t_float)2 * M_PI);
// 	// t_float	v = ((asinf(pos.y) + M_PI) / 2) / M_PI;

// 	return (rt_plane_get_pixel(obj->img, floor(u * (float)obj->img.width), floor(v * (float)obj->img.height)));
// }

int	rt_get_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_plane	pl;
	t_float	t;
	t_float	denum;
	t_float	num;

	if (!obj || obj->type != PLANE)
		return (0);
	pl = rt_get_transformed_plane(*obj);
	denum = vec3_dot(ray.dir, pl.normal);
	if (fabs(denum) < 1e-6)
		return (0);
	num = vec3_dot(vec3_subtract(pl.point, ray.pos), pl.normal);
	t = num / denum;
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->color = pl.color;
	// hit->color = calcul_color(obj, hit->pos);
	hit->normal = vec3_scale(pl.normal, 1 - 2 * (denum > 0));
	return (1);
}
