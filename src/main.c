/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/10/04 19:00:58 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	puterr_free(char *err, t_space *space)
{
	write(2, err, ft_strlen(err));
	free_space(space);
}

void	print_help(void)
{
	write(2, HELP_MSG, ft_strlen(HELP_MSG));
}

void	free_space(t_space *space)
{
	if (space)
	{
		if (space->objects)
			obj_lstfree(&(space->objects));
		if (space->lights)
			free(space->lights);
	}
}

int	main(int ac, char **av)
{
	char		*path;
	t_space		space;
	t_camera	camera;
	t_ambient	ambient;

	if ((ac < 2) || (ac > 4))
		return (puterr_free(ERROR_ARGS, NULL), 1);
	else if (ac == 2 && !ft_strncmp(av[1], "--help", 7))
		return (print_help(), 0);
	path = av[1];
	if (parser(path, &space, &camera, &ambient))
		return (puterr_free(ERROR_PARSING, &space), 1);
	print_space(&space);
	if (ac == 3 && (access(av[2], F_OK) == 0))
		mlx_render(&space, av[2], NULL);
	else if (ac == 4 && (access(av[2], F_OK) == 0) \
						&& (access(av[3], F_OK) == 0))
		mlx_render(&space, av[2], av[3]);
	else
		mlx_render(&space, NULL, NULL);
	if (space.fatal_error)
		puterr_free(FATAL_ERROR, NULL);
	free_space(&space);
	return (0);
}
