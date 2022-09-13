/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/13 01:23:44 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	objs_builder(char **tbl, t_space *space, int *to_switch)
{
	int	err;

	if (!ft_strncmp(tbl[0], "A", 2))
		err = build_ambient(tbl, &space->ambient);
	else if (!ft_strncmp(tbl[0], "C", 2))
		err = build_camera(tbl, &space->camera, to_switch);
	else if (!ft_strncmp(tbl[0], "L", 2))
		err = obj_lstadd(&space->objects, LIGHT, \
				(t_object *)build_light(tbl, *to_switch));
	else if (!ft_strncmp(tbl[0], "sp", 3))
		err = obj_lstadd(&space->objects, SPHERE, \
				(t_object *)build_sphere(tbl, *to_switch));
	else if (!ft_strncmp(tbl[0], "pl", 3))
		err = obj_lstadd(&space->objects, PLANE, \
				(t_object *)build_plane(tbl, *to_switch));
	else if (!ft_strncmp(tbl[0], "cy", 3))
		err = obj_lstadd(&space->objects, CYLINDER, \
				(t_object *)build_cylinder(tbl, *to_switch));
	else
		err = 1;
	return (err);
}

int	sub_parser(t_space *space, int *to_switch, int fd)
{
	char	*str;
	char	**tbl;
	int		err;

	err = 0;
	str = get_next_line(fd);
	while (str && !err)
	{
		if (!(*str == '\n') && !(*str == '#') && !line_is_space(str))
		{
			tbl = ft_split(str, ' ');
			err = objs_builder(tbl, space, to_switch);
			ft_freetbl(tbl, -1);
			free(str);
			str = NULL;
			if (err)
				break ;
		}
		if (str)
			free(str);
		str = get_next_line(fd);
	}
	return (err);
}

int	parser(char *path, t_space *space)
{
	int		err;
	int		fd;
	int		to_switch;

	init_parser_params(space, &to_switch);
	if (check_rt(path))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = sub_parser(space, &to_switch, fd);
	close(fd);
	if (!err && check_space_null(space))
		return (-1);
	return (err);
}
