
#include "minirt.h"

static void	*rt_draw_frame_thread(void *tv)
{
	int			x;
	int			y;
	t_ray		ray;
	t_thread	*t;

	t = tv;
	x = ((WIN_WIDTH) * (t->id - 1) / THREAD_NB);
	while (x < ((WIN_WIDTH) * t->id) / THREAD_NB)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			ray = rt_get_view_ray(*t->data->cam, x, y);
			ray.hit = rt_get_closest_hit(t->data, ray);
			t->data->obj_per_pixel[x][y] = ray.hit.obj;
			if (ray.hit.obj)
				rt_viewer_draw_pixel(t->data, x, y, \
									rt_get_hit_color(t->data, ray));
			y++;
		}
		x++;
	}
	return (tv);
}

static void	rt_launch_threads(t_data *data)
{
	int			i;
	t_thread	*t;

	i = 0;
	while (i < THREAD_NB)
	{
		t = &data->thread[i];
		t->id = i + 1;
		t->data = data;
		if (pthread_create(&t->thread, 0, rt_draw_frame_thread, t))
			rt_error_exit(data, 0);
		i++;
	}
}

static void	rt_wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < THREAD_NB)
	{
		if (pthread_join(data->thread[i].thread, NULL))
			rt_error_exit(data, 0);
		i++;
	}
}

void	rt_viewer_thread_handler(t_data *data)
{
	if (ENABLE_THREAD)
	{
		rt_launch_threads(data);
		rt_wait_for_threads(data);
	}
	else
		rt_draw_frame(data);
}