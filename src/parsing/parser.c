/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/06 17:17:12 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sub_parser(char **tbl, t_space *space)
{
	int	err;

	if (!ft_strncmp(tbl[0], "A", 2))
		err = build_ambient(tbl, &space->ambient);
	else if (!ft_strncmp(tbl[0], "C", 2))
		err = build_camera(tbl, &space->camera);
	else if (!ft_strncmp(tbl[0], "L", 2))
		err = obj_lstadd(&space->objects, LIGHT, \
				(t_object *)build_light(tbl));
	else if (!ft_strncmp(tbl[0], "sp", 3))
		err = obj_lstadd(&space->objects, SPHERE, \
				(t_object *)build_sphere(tbl));
	else if (!ft_strncmp(tbl[0], "pl", 3))
		err = obj_lstadd(&space->objects, PLANE, \
				(t_object *)build_plane(tbl));
	else if (!ft_strncmp(tbl[0], "cy", 3))
		err = obj_lstadd(&space->objects, CYLINDER, \
				(t_object *)build_cylinder(tbl));
	else
		err = 1;
	return (err);
}

int	check_space_null(t_space *space)
{
	if (!space->ambient && !space->camera && !space->objects && !space->lights)
		return (1);
	return (0);
}

int	line_is_space(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (i == len)
		return (1);
	return (0);
}

int	parser(char *path, t_space *space)
{
	int		err;
	int		fd;
	char	*str;
	char	**tbl;

	space->ambient = NULL;
	space->camera = NULL;
	space->objects = NULL;
	space->lights = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	err = 0;
	str = get_next_line(fd);
	while (str && !err)
	{
		if (!(*str == '\n') && !(*str == '#') && !line_is_space(str))
		{
			printf("I entered here with this str: %s\n", str);
			tbl = ft_split(str, ' ');
			err = sub_parser(tbl, space);
			ft_freetbl(tbl, -1);
			free(str);
			if (err)
				break ;
		}
		str = get_next_line(fd);
	}
	close(fd);
	if (check_space_null(space))
		return (-1);
	return (err);
}

void	print_space(t_space *space)
{
	t_obj_lst		*o;
	t_object		*obj;

	printf("\n~~~~ Space Layout ~~~~\n\n");
	printf("##### AMBIENT\t=> brightness(%.1f)\t\t\t\t\t\t\t\trgb(%zu,%zu,%zu) \n", space->ambient->lighting_ratio, space->ambient->r, space->ambient->g, space->ambient->b);
	printf("-<[0] CAMERA\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tfov(%zu) \n", space->camera->x, space->camera->y, space->camera->z, space->camera->vec_x, space->camera->vec_y, space->camera->vec_z, space->camera->fov);
	o = space->objects;
	while (o)
	{
		obj = (t_object *)(o->content);
		if (o->type == LIGHT)
			printf("((*)) LIGHT\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tbrightness(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", obj->l.x, obj->l.y, obj->l.z, obj->l.brightness_ratio, obj->l.r, obj->l.g, obj->l.b);
		else if (o->type == SPHERE)
			printf("  o   SPHERE\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tdiameter(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", obj->sp.x, obj->sp.y, obj->sp.z, obj->sp.diameter, obj->sp.r, obj->sp.g, obj->sp.b);
		else if (o->type == PLANE)
			printf(" [X]  PLANE\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\t\t\t\t\trgb(%zu,%zu,%zu) \n", obj->pl.x, obj->pl.y, obj->pl.z, obj->pl.vec_x, obj->pl.vec_y, obj->pl.vec_z, obj->pl.r, obj->pl.g, obj->pl.b);
		else if (o->type == CYLINDER)
			printf(" o=o  CYLINDER\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tdiameter(%.1f) height(%.1f)\trgb(%zu,%zu,%zu) \n", obj->cy.x, obj->cy.y, obj->cy.z, obj->cy.vec_x, obj->cy.vec_y, obj->cy.vec_z, obj->cy.diameter, obj->cy.height, obj->cy.r, obj->cy.g, obj->cy.b);
		o = o->next;
	}
}
