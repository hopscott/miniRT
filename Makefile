# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 19:55:04 by swillis           #+#    #+#              #
#    Updated: 2022/10/05 17:17:29 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Dirs ==========================================

SRC_DIR := src
INC_DIR := include
LIB_DIR := lib
BIN_DIR := .

# Exes ==========================================

EXE := $(BIN_DIR)/miniRT

# Compilation ====================================

CC := cc 
LDFLAGS ?= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -g

# Src files ======================================

HEADERS := 	$(INC_DIR)/libft.h\

SRCS	:= 	$(SRC_DIR)/camera/hits.c\
			$(SRC_DIR)/camera/matrix.c\
			$(SRC_DIR)/camera/camera_lookat_mat.c\
			$(SRC_DIR)/camera/rays.c\
			$(SRC_DIR)/camera/shading_light.c\
			$(SRC_DIR)/camera/shading_normal.c\
			$(SRC_DIR)/camera/shading_rgb.c\
			$(SRC_DIR)/camera/shading_uv.c\
			$(SRC_DIR)/camera/shading_uv_cy.c\
			$(SRC_DIR)/camera/shading.c\
			$(SRC_DIR)/intersector/cylinder_intersection.c\
			$(SRC_DIR)/intersector/init_center_cy_cam.c\
			$(SRC_DIR)/intersector/light_intersection.c\
			$(SRC_DIR)/intersector/plane_intersection.c\
			$(SRC_DIR)/intersector/sphere_intersection.c\
			$(SRC_DIR)/parser/ambient.c\
			$(SRC_DIR)/parser/camera.c\
			$(SRC_DIR)/parser/cylinder.c\
			$(SRC_DIR)/parser/light.c\
			$(SRC_DIR)/parser/object_list.c\
			$(SRC_DIR)/parser/parser_utils.c\
			$(SRC_DIR)/parser/parser_utils2.c\
			$(SRC_DIR)/parser/parser.c\
			$(SRC_DIR)/parser/plane.c\
			$(SRC_DIR)/parser/sphere.c\
			$(SRC_DIR)/parser/utils.c\
			$(SRC_DIR)/printer/printer_utils.c\
			$(SRC_DIR)/printer/printer.c\
			$(SRC_DIR)/vec/adv_ops.c\
			$(SRC_DIR)/vec/basic_ops.c\
			$(SRC_DIR)/vec/utils.c\
			$(SRC_DIR)/visualizer/mlx_render_utils.c\
			$(SRC_DIR)/visualizer/mlx_render.c\
			$(SRC_DIR)/visualizer/space_render_utils.c\
			$(SRC_DIR)/visualizer/space_render.c\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/utils.c\

# Make all ========================================

all : miniRT

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

# Libs ==========================================

LIBFT := $(LIB_DIR)/libft/libft.a

$(LIBFT) :
	make -C lib/libft -f Makefile

$(ULIMIT) :
	ulimit -s 65536

# Recipes ========================================

miniRT : $(OBJS) $(LIBFT) $(ULIMIT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(EXE)

# Cleanup ========================================

clean:
	make -C lib/libft -f Makefile clean
	rm -f $(OBJS)

fclean : clean
	make -C lib/libft -f Makefile fclean
	rm -f $(EXE)
	rm -f "hit.txt" "shading.txt"

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
