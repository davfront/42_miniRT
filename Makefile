# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:34:41 by dapereir          #+#    #+#              #
#    Updated: 2023/06/08 14:01:05 by dapereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	miniRT

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SRCS_FILES			=	\
						color/rgb.c\
						color/rgb_by_int.c\
						color/rgb_to_int.c\
						\
						vec3/vec3.c\
						vec3/vec3_add.c\
						vec3/vec3_subtract.c\
						vec3/vec3_multiply.c\
						vec3/vec3_scale.c\
						vec3/vec3_cross.c\
						vec3/vec3_normalize.c\
						vec3/vec3_dot.c\
						vec3/vec3_length.c\
						vec3/vec3_length_squared.c\
						vec3/vec3_equals.c\
						\
						utils/rt_init.c\
						utils/rt_delete.c\
						utils/rt_error_exit.c\
						\
						parse/rt_parse.c\
						\
						viewer/rt_viewer_start.c\
						viewer/rt_viewer_destroy.c\
						viewer/rt_viewer_hooks.c\
						viewer/rt_viewer_on_close.c\
						viewer/rt_viewer_render_frame.c\
						viewer/rt_viewer_draw_pixel.c\
						\
						raytracer/rt_get_view_ray.c\
						raytracer/rt_draw_frame.c\
						raytracer/rt_hit_default.c\
						raytracer/rt_get_plane_hit.c \
						raytracer/rt_get_sphere_hit.c\
						raytracer/rt_get_closest_hit.c\
						\
						main.c\

SRCS_DIR			=	./src
SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_FILES			=	$(SRCS_FILES:.c=.o)
OBJS_DIR			=	./obj
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

HEADER_DIR			=	./include
HEADER_FILES		=	minirt.h key_linux.h vec3.h
HEADER				=	$(addprefix $(HEADER_DIR)/, $(HEADER_FILES))
HEADER_INC			=	-I $(HEADER_DIR)

MLX_DIR				=	./minilibx-linux
MLX					=	$(MLX_DIR)/libmlx.a
MLX_INC				=	-I $(MLX_DIR)
MLX_OBJ_FLAGS		=	-I/usr/include $(HEADER_INC) $(MLX_INC) -O3
MLX_FLAGS			=	-L $(MLX_DIR) -l mlx -L/usr/lib $(MLX_INC) -lXext -lX11 -lm -lz

FT_DIR				=	./libft
FT					=	$(FT_DIR)/libft.a
FT_INC				=	-I $(FT_DIR)/include
FT_FLAGS			=	-L $(FT_DIR) -l ft

.PHONY: all
all:				$(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c Makefile $(MLX) $(FT) $(HEADER)
					mkdir -p $(@D)
					$(CC) $(CFLAGS) $(MLX_OBJ_FLAGS) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(MLX) $(FT)
					$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(FT_FLAGS) -o $(NAME)

$(MLX):
					$(MAKE) -C $(MLX_DIR)

$(FT):
					$(MAKE) -C $(FT_DIR)

.PHONY: clean
clean:
					$(RM) $(OBJS_DIR)
					$(MAKE) -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					$(RM) $(NAME)
					$(MAKE) -C $(MLX_DIR) clean
					$(MAKE) -C $(FT_DIR) fclean

.PHONY: re
re:					fclean
					$(MAKE) all
