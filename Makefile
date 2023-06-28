# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atchougo <atchougo@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 16:34:41 by dapereir          #+#    #+#              #
#    Updated: 2023/06/28 14:06:13 by atchougo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET				=	\033[0m
RED					=	\033[0;31m
RED_BOLD			=	\033[1;31m
GREEN				=	\033[0;32m
GREEN_BOLD			=	\033[1;32m
YELLOW				=	\033[0;33m
YELLOW_BOLD			=	\033[1;33m
CYAN				=	\033[0;36m
CYAN_BOLD			=	\033[1;36m
ERASE				=	\033[2K\033[1A\r

NAME				=	miniRT

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -pthread -MD -g3
RM					=	rm -rf

SRCS_FILES			=	\
						color/rgb.c\
						color/rgb_int.c\
						color/rgb_to_int.c\
						color/rgb_clamp.c\
						color/rgb_add.c\
						color/rgb_subtract.c\
						color/rgb_multiply.c\
						color/rgb_scale.c\
						color/rgb_mix.c\
						\
						vec3/vec3.c\
						vec3/vec3_add.c\
						vec3/vec3_subtract.c\
						vec3/vec3_multiply.c\
						vec3/vec3_scale.c\
						vec3/vec3_cross.c\
						vec3/vec3_normalize.c\
						vec3/vec3_reflect.c\
						vec3/vec3_dot.c\
						vec3/vec3_length.c\
						vec3/vec3_length_squared.c\
						vec3/vec3_equals.c\
						\
						utils/rt_delete.c\
						utils/rt_error.c\
						utils/rt_exit.c\
						utils/rt_error_exit.c\
						utils/rt_strs_len.c\
						utils/rt_print_fps.c \
						\
						parse/rt_parse_uint.c\
						parse/rt_parse_rgb.c\
						parse/rt_parse_float.c\
						parse/rt_parse_vec3.c\
						parse/rt_parse_input.c\
						parse/rt_parse_line.c\
						parse/rt_parse_ambient_light.c\
						parse/rt_parse_camera.c\
						parse/rt_parse_light.c\
						parse/rt_parse_obj_plane.c\
						parse/rt_parse_obj_sphere.c\
						parse/rt_parse_obj_cylinder.c\
						parse/rt_parse_line_error_exit.c\
						parse/rt_parse_value_error_exit.c\
						parse/rt_parse.c\
						\
						viewer/rt_viewer_start.c\
						viewer/rt_viewer_destroy.c\
						viewer/rt_viewer_hooks.c\
						viewer/rt_viewer_on_close.c\
						viewer/rt_viewer_render_frame.c\
						viewer/rt_viewer_draw_pixel.c\
						viewer/rt_viewer_thread_handler.c\
						\
						raytracer/rt_get_view_ray.c\
						raytracer/rt_draw_frame.c\
						raytracer/rt_draw_frame_thread.c \
						raytracer/rt_hit_default.c\
						raytracer/rt_get_plane_hit.c \
						raytracer/rt_get_sphere_hit.c\
						raytracer/rt_get_obj_hit.c\
						raytracer/rt_get_closest_hit.c\
						raytracer/rt_get_hit_color.c\
						\
						main.c\

SRCS_DIR			=	./src
SRCS				=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_FILES			=	$(SRCS_FILES:.c=.o)
DEPS_FILES			=	$(SRCS_FILES:.c=.d)
OBJS_DIR			=	./obj
OBJS				=	$(addprefix $(OBJS_DIR)/, $(OBJS_FILES))
DEPS				=	$(addprefix $(OBJS_DIR)/,$(DEPS_FILES))

HEADER_DIR			=	./include
HEADER_FILES		=	key_linux.h rgb.h vec3.h scene.h debug.h minirt.h
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

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(MLX) $(FT)
					@mkdir -p $(@D)	
					@printf "$(CYAN)[Compiling]$(RESET) $<\n"
					@$(CC) $(CFLAGS) $(MLX_OBJ_FLAGS) $(FT_INC) -c $< -o $@

$(NAME):			$(OBJS) $(MLX) $(FT)
					@printf "$(YELLOW)[Linking]  $(RESET) %s\n" $@
					@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(FT_FLAGS) -o $(NAME)
					@echo "$(GREEN_BOLD)miniRT is ready$(RESET)"

$(MLX):
					@echo "$(PURPLE)[Making]    MLX $(RESET)"
					@$(MAKE) -C $(MLX_DIR)

$(FT):
					@echo "$(PURPLE)[Making]    Libft $(RESET)"
					@$(MAKE) -C $(FT_DIR)

.PHONY: clean
clean:
					@echo "$(RED_BOLD)[Cleaning]$(RESET)"
					@$(RM) $(OBJS_DIR)
					@$(MAKE) -C $(FT_DIR) clean

.PHONY: fclean
fclean:				clean
					@$(RM) $(NAME)
					@$(MAKE) -C $(MLX_DIR) clean
					@$(MAKE) -C $(FT_DIR) fclean

.PHONY: re
re:					fclean
					@$(MAKE) all

-include $(DEPS)