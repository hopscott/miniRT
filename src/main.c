/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 17:45:16 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	char		*path;
	t_list		*objects;
	t_ambient	*a;

	if (ac != 2)
		return (1);
	path = av[1];
	objects = NULL;
	parser(path, &objects);

	printf("> %d\n", objects->type);
	a = (t_ambient *)objects->content;
	printf("> %f %zu,%zu,%zu\n", a->lighting_ratio, a->r, a->g, a->b);
	
	return (0);
}
