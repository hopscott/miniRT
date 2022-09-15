/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/09/11 00:30:49 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 100

int			ft_isspace(char c);
int			ft_isnum(char c);
size_t		ft_strlen(char *s);
size_t		strlen_eol(char *str);
char		*ft_freestr(char *s);
int			ft_atoi(char *nptr);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcpy(char *dst, char *src, size_t size);
size_t		ft_strlen_eol(char *s);
char		*ft_strjoin_eol(char *s1, char *s2);
char		*ft_strndup(char *s, size_t n);
void		ft_bzero(char *s, size_t n);
char		*get_next_line(int fd);
char		**ft_freetbl(char **tbl, int pos);
int			ft_wordcount(char *str, char c);
char		**ft_split(char *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
double		ft_atod(char *str);
void		ft_swap_double(double *a, double *b);

#endif
