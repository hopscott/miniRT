/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 16:05:59 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	char	*path;
	int		fd;
	char	*str;
	char	**tbl;

	if (ac != 2)
		return (1);
	path = av[1];
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
}
