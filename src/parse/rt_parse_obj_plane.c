/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_obj_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/20 06:52:30 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_parse_obj_plane(t_data *data, char **strs)
{
	t_obj	obj;
	t_obj	*content;
	t_list	*node;
	int w;
	int h;

	if (!data || !strs)
		rt_parse_line_error_exit(data, "plane: no data");
	if (rt_strs_len(strs) != 3)
		rt_parse_line_error_exit(data, "plane: 3 arguments expected");
	obj.type = PLANE;
	if (!rt_parse_vec3(strs[0], &obj.plane.point))
		rt_parse_value_error_exit(data, "plane", "point", strs[0]);
	if (!rt_parse_vec3_dir(strs[1], &obj.plane.normal))
		rt_parse_value_error_exit(data, "plane", "normal", strs[1]);
	if (!rt_parse_rgb(strs[2], &obj.plane.color))
		rt_parse_value_error_exit(data, "plane", "color", strs[2]);
	obj.tf = rt_get_plane_transformations(obj.plane);
	obj.img.img = mlx_xpm_file_to_image(data->mlx, "earth.xpm", &w, &h);
	obj.img.width = w;
	obj.img.height = h;
	obj.img.addr = mlx_get_data_addr(obj.img.img, &obj.img.bpp, &obj.img.len, &obj.img.endian);
	content = ft_calloc(1, sizeof(t_obj));
	if (!content)
		rt_parse_line_error_exit(data, "plane: t_obj alloc failed");
	*content = obj;
	node = ft_lstnew(content);
	if (!node)
		rt_parse_line_error_exit(data, "plane: t_list alloc failed");
	ft_lstadd_back(&data->obj_lst, node);
}
