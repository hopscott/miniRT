/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 18:00:30 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	char		*path;
	t_list		*objects;
	t_ambient	*a;
	t_camera	*c;

	if (ac != 2)
		return (1);
	path = av[1];
	objects = NULL;
	parser(path, &objects);

	printf("> %d\n", objects->type);
	a = (t_ambient *)objects->content;
	printf("> %f %zu,%zu,%zu\n", a->lighting_ratio, a->r, a->g, a->b);
	
	printf("> %d\n", (*objects->next).type);
	c = (t_camera *)(*objects->next).content;
	printf("> %f,%f,%f %f,%f,%f %zu\n", c->x, c->y, c->z, c->vec_x, c->vec_y, c->vec_z, c->fov);
	
	return (0);
}
