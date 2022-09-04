# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 19:55:04 by swillis           #+#    #+#              #
#    Updated: 2022/09/04 22:57:40 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name ==========================================

NAME := miniRT.a #I'm not sure if we are suppose to build a library

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
# CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -g -fsanitize=address
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -g

# Src files ======================================

HEADERS := 	$(INC_DIR)/libft.h\

SRCS	:= 	$(SRC_DIR)/parsing/parser.c\
			$(SRC_DIR)/parsing/object_list.c\
			$(SRC_DIR)/parsing/errorinizer.c\
			$(SRC_DIR)/parsing/ambient.c\
			$(SRC_DIR)/parsing/camera.c\
			$(SRC_DIR)/parsing/light.c\
			$(SRC_DIR)/parsing/sphere.c\
			$(SRC_DIR)/parsing/plane.c\
			$(SRC_DIR)/parsing/cylinder.c\
			$(SRC_DIR)/vec3/init.c\
			$(SRC_DIR)/vec3/basic_ops.c\
			$(SRC_DIR)/vec3/adv_ops.c\
			$(SRC_DIR)/camera/matrix.c\
			$(SRC_DIR)/camera/rays.c\
			$(SRC_DIR)/intersection/light_intersection.c\
			$(SRC_DIR)/intersection/plane_intersection.c\
			$(SRC_DIR)/intersection/sphere_intersection.c\
			$(SRC_DIR)/visuals/mlx_render.c\
			$(SRC_DIR)/visuals/space_render.c\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/utils.c\

# Make all ========================================

all : $(NAME)

$(NAME): miniRT

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

# Objects ========================================

OBJS := $(SRCS:.c=.o)

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
	rm -rf $(OBJS)

fclean : clean
	make -C lib/libft -f Makefile fclean
	rm -rf $(EXE)

# Additional ========================================

re : fclean all

.PHONY : all clean fclean re
