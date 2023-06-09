/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/09 22:37:51 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse(t_data *data)
{
	if (!data)
		rt_error_exit(data, "parsing failed");
	data->title = "Hard coded data";

	// A	0.2				255,255,255

	data->al.ratio = 0.2;
	data->al.color = rgb(255, 255, 255);

	// C	-50,0,20		0,0,1			70
	data->cam.pos = vec3(-100, 0, 20);
	data->cam.dir = vec3_normalize(vec3(1, 0, 0));
	data->cam.up = vec3_normalize(vec3(0, 1, 0));
	data->cam.fov = (t_float)70 * M_PI / 180;
	data->cam.aspect_ratio = (t_float)WIN_WIDTH / WIN_HEIGHT;
	data->cam.right = vec3_cross(data->cam.up, data->cam.dir);
	data->cam.top = vec3_cross(data->cam.dir, data->cam.right);

	// L	-40,0,30		0.7				255,255,255
	data->lights_size = 1;
	data->lights = calloc(data->lights_size, sizeof(t_light));
	// todo: protect malloc
	data->lights[0].pos = vec3(-40, 0, 30);
	data->lights[0].color = rgb(255, 255, 255);
	data->lights[0].ratio = 0.7;

	// objects
	data->objs_size = 4;
	data->objs = calloc(data->objs_size, sizeof(t_obj));
	// todo: protect malloc

	// pl	0,0,0			0,1.0,0			255,0,225
	data->objs[0].type = PLANE;
	data->objs[0].plane.point = vec3(0, 0, 0);
	data->objs[0].plane.normal = vec3_normalize(vec3(0, 1, 0));
	data->objs[0].plane.color = rgb(255, 0, 255);

	// sp	0,0,20			20				255,0,0
	data->objs[1].type = SPHERE;
	data->objs[1].sphere.center = vec3(0, 0, 20);
	data->objs[1].sphere.radius = (t_float)20 / 2;
	data->objs[1].sphere.color = rgb(255, 0, 0);

	// cy	50.0,0.0,20.6	0,0,1.0		14.2	21.42		10,0,255
	data->objs[2].type = CYLINDER;
	data->objs[2].cylinder.center = vec3(50.0, 0.0, 20.6);
	data->objs[2].cylinder.axis = vec3_normalize(vec3(50.0, 0.0, 20.6));
	data->objs[2].cylinder.radius = (t_float)14.2 / 2;
	data->objs[2].cylinder.height = 21.42;
	data->objs[2].cylinder.color = rgb(10, 0, 255);

	// sp2
	data->objs[3].type = SPHERE;
	data->objs[3].sphere.center = vec3(0, 18, 38);
	data->objs[3].sphere.radius = (t_float)40 / 2;
	data->objs[3].sphere.color = rgb(0, 255, 0);
}
