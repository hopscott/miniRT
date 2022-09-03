/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/09/03 01:57:15 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	space_free(t_space *space)
{
	obj_lstfree(&space->objects);
	// vec3_free_multi(space->ambient->rgb, space->camera, NULL);
	// free();
	free(space->ambient);
	free(space->camera);
	free(space->lights);
}

int	main(int ac, char **av)
{
	char		*path;
	t_space		space;

	if (ac != 2)
		return (putstr_error(ERROR_ARGS), 1);
	else if (ac == 2 && !ft_strncmp(av[1], "--help", 7))
		return (print_help(), 0);
	path = av[1];
	if (parser(path, &space))
		return (putstr_error(ERROR_PARSING), 1);
	print_space(&space);
	mlx_render(&space);
	space_free(&space);
	return (0);
}
