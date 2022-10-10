/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 00:39:13 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	objs_builder1(char **tbl, t_space *space, t_ambient *ambient)
{
	int	err;

	err = 0;
	if (!ft_strncmp(tbl[0], "A", 2) || !ft_strncmp(tbl[0], "a", 2))
	{
		if (space->ambient)
			return (2);
		space->amb = 1;
		err = build_ambient(tbl, ambient);
	}
	return (err);
}

int	objs_builder2(char **tbl, t_space *space, int *to_switch, t_camera *camera)
{
	int	err;

	err = 0;
	if (!ft_strncmp(tbl[0], "C", 2) || !ft_strncmp(tbl[0], "c", 2))
	{
		if (space->cam)
			return (2);
		space->cam = 1;
		err = build_camera(tbl, camera, to_switch);
	}
	return (err);
}

int	objs_builder3(char **tbl, t_space *space, int *to_switch)
{
	int	err;

	err = 0;
	if (!ft_strncmp(tbl[0], "L", 2) || !ft_strncmp(tbl[0], "l", 2))
		err = obj_lstadd(&space->objects, LIGHT, \
				(t_object *)build_light(tbl, *to_switch), tbl);
	else if (!ft_strncmp(tbl[0], "sp", 3) || !ft_strncmp(tbl[0], "SP", 3))
		err = obj_lstadd(&space->objects, SPHERE, \
				(t_object *)build_sphere(tbl, *to_switch), tbl);
	else if (!ft_strncmp(tbl[0], "pl", 3) || !ft_strncmp(tbl[0], "PL", 3))
		err = obj_lstadd(&space->objects, PLANE, \
		(t_object *)build_plane(space, tbl, *to_switch), tbl);
	else if (!ft_strncmp(tbl[0], "cy", 3) || !ft_strncmp(tbl[0], "CY", 3))
		err = obj_lstadd(&space->objects, CYLINDER, \
			(t_object *)build_cylinder(tbl, *to_switch), tbl);
	else if ((ft_strncmp(tbl[0], "a", 3) && ft_strncmp(tbl[0], "A", 3)) && \
			(ft_strncmp(tbl[0], "c", 3) && ft_strncmp(tbl[0], "C", 3)))
		err = 1;
	return (err);
}

int	sub_parser(t_space *space, int fd, t_camera *camera, t_ambient *ambient)
{
	char	*str;
	char	**tbl;
	int		err;
	int		to_switch;

	err = 0;
	to_switch = 0;
	str = get_next_line(fd);
	while (!err && str)
	{
		if (!err && !(*str == '\n') && !(*str == '#') && !line_is_space(str))
		{
			tbl = ft_split(str, ' ');
			err = objs_builder1(tbl, space, ambient);
			if (!err)
				err = objs_builder2(tbl, space, &to_switch, camera);
			if (!err)
				err = objs_builder3(tbl, space, &to_switch);
			ft_freetbl(tbl, -1);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (err);
}

int	parser(char *path, t_space *space, t_camera *camera, t_ambient *ambient)
{
	int			err;
	int			fd;

	init_parser_params(space);
	if (check_rt(path))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = sub_parser(space, fd, camera, ambient);
	if (!err)
	{
		space->camera = camera;
		space->ambient = ambient;
		if (check_space_null(space))
			return (-1);
		cy_init_cam_center(space->camera, &(space->objects));
	}
	return (err);
}
