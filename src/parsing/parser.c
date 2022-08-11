/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 17:38:59 by swillis          ###   ########.fr       */
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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && *lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_ambient	*build_ambient(char **tbl)
{
	t_ambient	*obj;
	char		**rgb;

	printf("Ambient lighting\n");
	obj = malloc(sizeof(t_ambient));
	if (!obj)
		return (NULL);
	obj->lighting_ratio = (double)ft_atoi(tbl[1]); // need to build atoi for doubles
	rgb = ft_split(tbl[2], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	return (obj);
}

int	parser(char *path, t_list **lst)
{
	int		fd;
	char	*str;
	char	**tbl;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (1);
	str = get_next_line(fd);
	while (str)
	{
		tbl = ft_split(str, ' ');
		if ((ft_strncmp(tbl[0], "A", 2)) == 0)
			ft_lstadd_back(lst, ft_lstnew(AMBIENT, build_ambient(tbl)));
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
	return (0);
}
