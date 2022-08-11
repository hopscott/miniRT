/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 17:57:15 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			ft_lstadd_back(lst, ft_lstnew(CAMERA, build_camera(tbl)));
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
