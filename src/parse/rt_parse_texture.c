/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:30:58 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/24 16:15:30 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	rt_parse_chess_is_str_valid(char *s)
{
	int		n;
	char	*sep;

	n = 0;
	if (ft_strncmp(s, "chess:", 6) != 0)
		return (0);
	sep = ft_strchr(s, ':');
	while (sep)
	{
		n++;
		if (n > 4 || !sep[1] || sep[1] == ':')
			return (0);
		sep = ft_strchr(sep + 1, ':');
	}
	return (n == 4);
}

static int	rt_parse_chess(char *s, t_chess *chess_p)
{
	char	**args;
	t_chess	chess;

	if (!s || !chess_p)
		return (0);
	if (!rt_parse_chess_is_str_valid(s))
		return (0);
	args = ft_split(s + 6, ":");
	if (!args)
		return (rt_error("rt_parse_chess: split failed\n"), 0);
	if (!rt_parse_rgb(args[0], &chess.color1))
		return (ft_free_split(&args), 0);
	if (!rt_parse_rgb(args[1], &chess.color2))
		return (ft_free_split(&args), 0);
	if (!rt_parse_float_len(args[2], &chess.size.x))
		return (ft_free_split(&args), 0);
	if (!rt_parse_float_len(args[3], &chess.size.y))
		return (ft_free_split(&args), 0);
	*chess_p = chess;
	return (ft_free_split(&args), 1);
}

static int	rt_parse_xpm(t_data *data, char *s, t_img *xpm)
{
	char	buf[PATH_MAX];
	char	*path;
	char	*xpm_path;

	if (!s || !xpm)
		return (0);
	path = realpath(data->path, buf);
	if (!path)
		return (rt_error("rt_parse_xpm: realpath failed\n"), 0);
	path = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(data->title));
	if (!path)
		return (rt_error("rt_parse_xpm: ft_substr failed\n"), 0);
	xpm_path = ft_strjoin(path, ft_strchr(s, ':') + 1);
	if (!xpm_path)
		return (rt_error("rt_parse_xpm: ft_strjoin failed\n"), free(path), 0);
	xpm->img = mlx_xpm_file_to_image(data->mlx, \
									xpm_path, &xpm->width, &xpm->height);
	if (!xpm->img)
		return (free(path), free(xpm_path), 0);
	xpm->addr = mlx_get_data_addr(xpm->img, \
								&xpm->bpp, &xpm->len, &xpm->endian);
	return (free(path), free(xpm_path), 1);
}

int	rt_parse_texture(t_data *data, char *s, t_obj *obj)
{
	if (!s)
		return (0);
	if (ft_strncmp(s, "chess:", 6) == 0)
	{
		obj->tex_type = CHESS;
		return (rt_parse_chess(s, &obj->chess));
	}
	if (ft_strncmp(s, "xpm:", 4) == 0)
	{
		obj->tex_type = XPM;
		return (rt_parse_xpm(data, s, &obj->xpm));
	}
	obj->tex_type = COLOR;
	return (rt_parse_rgb(s, &obj->color));
}
