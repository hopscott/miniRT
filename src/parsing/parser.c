/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 17:14:56 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list	*ft_lstnew(int type, void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_list	**parser(char *path)
{
	int		fd;
	char	*str;
	char	**tbl;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		tbl = ft_split(str, ' ');
		if ((ft_strncmp(tbl[0], "A", 2)) == 0)
			printf("Ambient lighting\n");
		else if ((ft_strncmp(tbl[0], "C", 2)) == 0)
			printf("Camera\n");
		else if ((ft_strncmp(tbl[0], "L", 2)) == 0)
			printf("Light\n");
		else if ((ft_strncmp(tbl[0], "sp", 3)) == 0)
			printf("Sphere\n");
		else if ((ft_strncmp(tbl[0], "pl", 3)) == 0)
			printf("Plane\n");
		else if ((ft_strncmp(tbl[0], "cy", 3)) == 0)
			printf("Cylinder\n");
		ft_freetbl(tbl, -1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}
