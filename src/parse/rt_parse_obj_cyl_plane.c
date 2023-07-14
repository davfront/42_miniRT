#include "minirt.h"

static void	rt_add_bot_plane(t_data *data, t_obj obj, t_vec3 displacement)
{
	t_obj	new_obj;
	t_obj	*content;
	t_list	*node;

	if (!data)
		rt_parse_line_error_exit(data, "cylinder: no data");
	new_obj.type = CYLPLANE;
	new_obj.cyl_plane.color = obj.cylinder.color;
	new_obj.cyl_plane.radius = obj.cylinder.radius;
	new_obj.cyl_plane.normal = obj.cylinder.axis;
	new_obj.cyl_plane.point = vec3_subtract(obj.cylinder.center, displacement);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "cylinder: t_obj alloc failed");
	*content = new_obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "cylinder: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}

static void	rt_add_top_plane(t_data *data, t_obj obj, t_vec3 displacement)
{
	t_obj	new_obj;
	t_obj	*content;
	t_list	*node;

	if (!data)
		rt_parse_line_error_exit(data, "cylinder: no data");
	new_obj.type = CYLPLANE;
	new_obj.cyl_plane.color = obj.cylinder.color;
	new_obj.cyl_plane.radius = obj.cylinder.radius;
	new_obj.cyl_plane.normal = obj.cylinder.axis;
	new_obj.cyl_plane.point = vec3_add(obj.cylinder.center, displacement);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "cylinder: t_obj alloc failed");
	*content = new_obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "cylinder: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}

void	rt_parse_obj_cyl_plane(t_data *data, t_obj obj)
{
	t_vec3	displacement;

	if (!data)
		rt_parse_line_error_exit(data, "cylinder: no data");
	if (obj.type != CYLINDER)
		rt_parse_line_error_exit(data, "cylinder: should be cylinder");
	displacement = vec3_scale(obj.cylinder.axis, obj.cylinder.height / 2);
	rt_add_top_plane(data, obj, displacement);
	rt_add_bot_plane(data, obj, displacement);
}