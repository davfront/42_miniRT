#include "minirt.h"

static int	rt_is_in_disc(t_cyl_plane c_plane, t_hit *hit)
{
	if (vec3_length(vec3_subtract(hit->pos, c_plane.point)) <= c_plane.radius)
		return (1);
	else
	{
		*hit = rt_hit_default();
		return (0);
	}
}

int	rt_get_cyl_plane_hit(t_ray ray, t_obj *obj, t_float t_max, t_hit *hit)
{
	t_float	t;
	t_float	denum;
	t_float	num;
	t_cyl_plane	c_plane;

	if (!obj || obj->type != CYLPLANE)
		return (0);
	c_plane = obj->cyl_plane;
	denum = vec3_dot(ray.dir, c_plane.normal);
	if (!denum)
		return (0);
	num = vec3_dot(vec3_subtract(c_plane.point, ray.pos), c_plane.normal);
	t = num / denum;
	if (!isfinite(t) || t < T_MIN || t > t_max)
		return (0);
	if (!hit)
		return (1);
	*hit = rt_hit_default();
	hit->obj = obj;
	hit->dist = t;
	hit->color = c_plane.color;
	hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, hit->dist));
	hit->normal = vec3_normalize(vec3_scale(c_plane.normal, 1 - 2 * (denum > 0)));
	return (rt_is_in_disc(c_plane, hit));
}