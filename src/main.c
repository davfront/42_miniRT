/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:56:16 by dapereir          #+#    #+#             */
/*   Updated: 2023/07/19 01:52:27 by atchougo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	rt_init(&data);
    data.mlx = mlx_init();
	rt_parse(&data, argc, argv);
	rt_viewer_start(&data);
	rt_delete(&data);
	return (EXIT_SUCCESS);
}

// int	rt_viewer_on_keydown2(int keycode, t_data *data)
// {
//     (void)keycode;(void)data;
// 	exit(1);
// 	return (0);
// }

// t_rgb	get_pixel(char *addr, int x, int y, int len, int bpp)
// {
// 	char	*dst;
// 	int		color_int;

// 	dst = addr;
// 	dst += y * len;
// 	dst += x * (bpp / 8);
// 	color_int = *(unsigned int *)dst;
// 	return (rgb_int(color_int));
// }

// void	set_pixel(char *addr, int x, int y, t_rgb color, int len, int bpp)
// {
// 	char	*dst;
// 	int		color_int;

// 	color_int = rgb_to_int(color);
// 	dst = addr;
// 	dst += y * len;
// 	dst += x * (bpp / 8);
// 	*(unsigned int *)dst = color_int;
// }

// int main()
// {
//     void *mlx, *win, *img;
//     void *img2;
//     int w, h;
//     char *addr;
//     int bits_per_pixel; int size_line; int endian;
//     char *addr2;
//     int bits_per_pixel2; int size_line2; int endian2;
    
//     mlx = mlx_init();
//     win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Test Texture");
//     img = mlx_xpm_file_to_image(mlx, "ray.xpm", &w, &h);
//     img2 = mlx_new_image(mlx, w, h);
//     mlx_hook(win, 2, 1L << 0, rt_viewer_on_keydown2, 0);
//     addr = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
//     addr2 = mlx_get_data_addr(img2, &bits_per_pixel2, &size_line2, &endian2);
//     DEBUG("weight : %d, height : %d",w, h);
//     for(int i = 0; i < h; i++)
//     {
//         for(int j = 0; j < h; j++)
//         {
//             set_pixel(addr2, i, j, get_pixel(addr, i, j, size_line, bits_per_pixel), size_line2, bits_per_pixel2);
//         }
//     }
//     mlx_put_image_to_window(mlx, win, img2, 0, 0);
//     mlx_loop(mlx);
// }
