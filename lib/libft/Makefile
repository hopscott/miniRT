SRCS	=	ft_atoi.c\
			ft_atod.c\
			ft_strdup.c\
			ft_strjoin.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_split.c\
			ft_bzero.c\
			ft_strndup.c\
			get_next_line.c\
			ft_strncmp.c\
			ft_swap_double.c\

OBJS	= 	${SRCS:.c=.o}

NAME	= 	libft.a

CC	=	 cc

CFLAGS	= 	-Wall -Wextra -Werror -g

RM	= 	rm -rf

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
		ar rcs ${NAME} ${OBJS}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean	all

.PHONY:		all clean fclean re
