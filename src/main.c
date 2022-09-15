/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/09/15 18:14:20 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	space_free(t_space *space)
{
	t_camera	*cam;
	t_ambient	*amb;

	cam = space->camera;
	amb = space->ambient;
	obj_lstfree(&space->objects);
	vec3_free_multi(cam->xyz, cam->norm, amb->rgb, 0);
	free(space->lights);
}

int	main(int ac, char **av)
{
	char		*path;
	t_space		space;
	t_camera	camera;
	t_ambient	ambient;

	if (ac != 2)
		return (puterr_free(ERROR_ARGS, NULL), 1);
	else if (ac == 2 && !ft_strncmp(av[1], "--help", 7))
		return (print_help(), 0);
	path = av[1];
	if (parser(path, &space, &camera, &ambient))
		return (puterr_free(ERROR_PARSING, &space), 1);
	print_space(&space);
	mlx_render(&space);
	if (space.fatal_error)
		puterr_free(FATAL_ERROR, NULL);
	free_space(&space);
	return (0);
}
