/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/18 16:04:30 by swillis          ###   ########.fr       */
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
		err = light_lstadd(&space->lights, build_light(tbl));
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

int	parser(char *path, t_space *space)
{
	int		err;
	int		fd;
	char	*str;
	char	**tbl;

	space->ambient = NULL;
	space->camera = NULL;
	space->lights = NULL;
	space->objects = NULL;
	fd = open(path, O_RDONLY);
	if (!fd)
		return (1);
	err = 0;
	str = get_next_line(fd);
	while (str && !err)
	{
		tbl = ft_split(str, ' ');
		err = sub_parser(tbl, space);
		ft_freetbl(tbl, -1);
		free(str);
		if (err)
			break ;
		str = get_next_line(fd);
	}
	close(fd);
	return (err);
}

void	print_space(t_space *space)
{
	t_obj_lst		*o;
	t_light_lst		*l;
	t_object		*obj;
	
	printf("##### AMBIENT\t=> brightness(%.1f)\t\t\t\t\t\t\t\trgb(%zu,%zu,%zu) \n", space->ambient->lighting_ratio, space->ambient->r, space->ambient->g, space->ambient->b);
	printf("-<[0] CAMERA\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tfov(%zu) \n", space->camera->x, space->camera->y, space->camera->z, space->camera->vec_x, space->camera->vec_y, space->camera->vec_z, space->camera->fov);
	l = space->lights;
	while (l)
	{
		printf("((*)) LIGHT\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tbrightness(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", l->light->x, l->light->y, l->light->z, l->light->brightness_ratio, l->light->r, l->light->g, l->light->b);
		l = l->next;
	}
	o = space->objects;
	while (o)
	{
		obj = (t_object *)(o->content);
		if (o->type == SPHERE)
			printf("  o   SPHERE\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tradius(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", obj->sp.x, obj->sp.y, obj->sp.z, obj->sp.diameter, obj->sp.r, obj->sp.g, obj->sp.b);
		else if (o->type == PLANE)
			printf(" [X]  PLANE\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\t\t\t\t\trgb(%zu,%zu,%zu) \n", obj->pl.x, obj->pl.y, obj->pl.z, obj->pl.vec_x, obj->pl.vec_y, obj->pl.vec_z, obj->pl.r, obj->pl.g, obj->pl.b);
		else if (o->type == CYLINDER)
			printf(" o=o  CYLINDER\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tdiameter(%.1f) height(%.1f)\trgb(%zu,%zu,%zu) \n", obj->cy.x, obj->cy.y, obj->cy.z, obj->cy.vec_x, obj->cy.vec_y, obj->cy.vec_z, obj->cy.diameter, obj->cy.height, obj->cy.r, obj->cy.g, obj->cy.b);
		o = o->next;
	}
}
