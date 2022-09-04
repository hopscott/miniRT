/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:12:36 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/03 22:37:32 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	space_free(t_space *space)
{
	free(space->ambient);
	free(space->camera);
	obj_lstfree(&space->objects);
	light_lstfree(&space->lights);
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

