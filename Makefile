# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swillis <swillis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 18:15:41 by swillis           #+#    #+#              #
#    Updated: 2022/08/11 14:26:09 by swillis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name ==========================================

NAME := miniRT.a

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
CFLAGS ?= -Wall -Wextra -Werror -I$(INC_DIR) -I/usr/include -Imlx_linux -O3 -g -fsanitize=address

# Src files ======================================

HEADERS := 	$(INC_DIR)/libft.h\

SRCS	:= 	$(SRC_DIR)/parsing/parser.c\
			$(SRC_DIR)/main.c\

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
