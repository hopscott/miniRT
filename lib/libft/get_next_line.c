/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:25:01 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 17:29:33 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	bufflen_eol(char buff[])
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buff[i])
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

size_t	check_eol(char *str)
{
	size_t	i;

	if (!str)
		return (1);
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_concat(char *str, char buff[])
{
	char	*cat;
	size_t	slen;
	size_t	blen;
	size_t	i;
	size_t	j;

	slen = ft_strlen(str);
	blen = bufflen_eol(buff);
	cat = malloc(sizeof(cat) * (slen + blen + 1));
	if (!cat)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		cat[i] = str[i];
		i++;
	}
	j = 0;
	while (j < blen)
		cat[i++] = buff[j++];
	cat[i] = '\0';
	free(str);
	return (cat);
}

char	*ft_realign_buff(char *s, size_t i, char buff[])
{
	char	*tmp;
	size_t	len;

	len = BUFFER_SIZE - i;
	tmp = ft_strndup(&buff[i], len);
	if (!tmp)
		return (NULL);
	ft_bzero(buff, BUFFER_SIZE);
	i = 0;
	while (tmp && i < len)
	{
		buff[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (s);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	char			*str;
	int				rd;

	if ((fd < 0) || (fd > 1024))
		return (NULL);
	rd = -1;
	if (bufflen_eol(buffer) == 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			return (NULL);
	}
	str = ft_strndup(buffer, bufflen_eol(buffer));
	while (!check_eol(str))
	{
		ft_bzero(buffer, BUFFER_SIZE);
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		str = ft_concat(str, buffer);
	}
	return (ft_realign_buff(str, bufflen_eol(buffer), buffer));
}
