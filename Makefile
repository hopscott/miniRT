# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 19:55:04 by swillis           #+#    #+#              #
#    Updated: 2022/10/10 14:15:34 by omoudni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
LIB_DIR := lib
OBJ_DIR := build
BIN_DIR := .

# Exes ==========================================

EXE := $(BIN_DIR)/miniRT

# Compilation ====================================

CC := cc
LDFLAGS ?= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -g 

# # macOS
# LDFLAGS ?= -Lmlx -lmlx -framework OpenGL -framework AppKit
# CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -Imlx -O3 -g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/minirt.h\
			$(INC_DIR)/vec.h\
			$(INC_DIR)/libft.h\

SRCS	:= 	$(SRC_DIR)/camera/camera_lookat_matrix.c\
			$(SRC_DIR)/camera/matrix_operations.c\
			$(SRC_DIR)/camera/matrix_transpose.c\
			$(SRC_DIR)/intersector/cylinder_intersection.c\
			$(SRC_DIR)/intersector/cylinder_intersection_2.c\
			$(SRC_DIR)/intersector/init_center_cy_cam.c\
			$(SRC_DIR)/intersector/light_intersection.c\
			$(SRC_DIR)/intersector/plane_intersection.c\
			$(SRC_DIR)/intersector/sphere_intersection.c\
			$(SRC_DIR)/parser/build_ambient.c\
			$(SRC_DIR)/parser/build_camera.c\
			$(SRC_DIR)/parser/build_cylinder.c\
			$(SRC_DIR)/parser/build_light.c\
			$(SRC_DIR)/parser/build_plane.c\
			$(SRC_DIR)/parser/build_sphere.c\
			$(SRC_DIR)/parser/build_utils.c\
			$(SRC_DIR)/parser/object_list.c\
			$(SRC_DIR)/parser/parser.c\
			$(SRC_DIR)/parser/parser_checks.c\
			$(SRC_DIR)/parser/parser_init_free.c\
			$(SRC_DIR)/parser/parser_surface.c\
			$(SRC_DIR)/printers/matrix_printer.c\
			$(SRC_DIR)/printers/parsing_printer.c\
			$(SRC_DIR)/printers/parsing_printer_utils.c\
			$(SRC_DIR)/printers/progress_printer.c\
			$(SRC_DIR)/printers/screen_printer.c\
			$(SRC_DIR)/rays/cast_ray.c\
			$(SRC_DIR)/rays/nearest_hit.c\
			$(SRC_DIR)/shading/bump_mapping.c\
			$(SRC_DIR)/shading/checkerboard_textures.c\
			$(SRC_DIR)/shading/shading.c\
			$(SRC_DIR)/shading/shading_from_light.c\
			$(SRC_DIR)/shading/uv_mapping.c\
			$(SRC_DIR)/shading/uv_mapping_cy_utils.c\
			$(SRC_DIR)/vec/adv_ops.c\
			$(SRC_DIR)/vec/basic_ops.c\
			$(SRC_DIR)/vec/utils.c\
			$(SRC_DIR)/render/mlx_render.c\
			$(SRC_DIR)/render/mlx_render_utils.c\
			$(SRC_DIR)/render/space_render.c\
			$(SRC_DIR)/render/space_render_utils.c\
			$(SRC_DIR)/main.c\

# Make all ========================================

all : miniRT

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p 	$(OBJ_DIR) $(OBJ_DIR)/camera $(OBJ_DIR)/intersector $(OBJ_DIR)/parser $(OBJ_DIR)/printers $(OBJ_DIR)/rays $(OBJ_DIR)/render $(OBJ_DIR)/shading $(OBJ_DIR)/vec
	$(CC) $(CFLAGS) -c $< -o $@

# Objects ========================================

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libs ==========================================

LIBFT := $(LIB_DIR)/libft/libft.a

$(LIBFT) :
	make -C lib/libft -f Makefile

# Recipes ========================================

miniRT : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(EXE)

# Cleanup ========================================

clean:
	make -C lib/libft -f Makefile clean
	rm -rf $(OBJS) $(OBJ_DIR)

fclean : clean
	make -C lib/libft -f Makefile fclean
	rm -f $(EXE)
	rm -f "hit.txt" "shading.txt"

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
