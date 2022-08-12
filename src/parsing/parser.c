/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 23:14:14 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parser(char *path, t_list **lst)
{
	int		fd;
	char	*str;
	char	**tbl;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (1);
	str = get_next_line(fd);
	while (str)
	{
		tbl = ft_split(str, ' ');
		if ((ft_strncmp(tbl[0], "A", 2)) == 0)
			ft_lstadd_back(lst, ft_lstnew(AMBIENT, build_ambient(tbl)));
		else if ((ft_strncmp(tbl[0], "C", 2)) == 0)
			ft_lstadd_back(lst, ft_lstnew(CAMERA, build_camera(tbl)));
		else if ((ft_strncmp(tbl[0], "L", 2)) == 0)
			ft_lstadd_back(lst, ft_lstnew(LIGHT, build_light(tbl)));
		else if ((ft_strncmp(tbl[0], "sp", 3)) == 0)
			ft_lstadd_back(lst, ft_lstnew(SPHERE, build_sphere(tbl)));
		else if ((ft_strncmp(tbl[0], "pl", 3)) == 0)
			ft_lstadd_back(lst, ft_lstnew(PLANE, build_plane(tbl)));
		else if ((ft_strncmp(tbl[0], "cy", 3)) == 0)
			ft_lstadd_back(lst, ft_lstnew(CYLINDER, build_cylinder(tbl)));
		ft_freetbl(tbl, -1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	ft_print_objects(t_list **lst)
{
	t_list		*elem;
	t_object	*obj;

	elem = *lst;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == AMBIENT)
			printf("AMBIENT\t\t=> %f %zu,%zu,%zu \n", \
				obj->a.lighting_ratio, obj->a.r, obj->a.g, obj->a.b);
		else if (elem->type == CAMERA)
			printf("CAMERA\t\t=> %f,%f,%f %f,%f,%f %zu \n", \
			obj->c.x, obj->c.y, obj->c.z, obj->c.vec_x, obj->c.vec_y, obj->c.vec_z, obj->c.fov);
		else if (elem->type == LIGHT)
			printf("LIGHT\t\t=> %f,%f,%f %f %zu,%zu,%zu \n", \
			obj->l.x, obj->l.y, obj->l.z, obj->l.brightness_ratio, obj->l.r, obj->l.g, obj->l.b);
		else if (elem->type == SPHERE)
			printf("SPHERE\t\t=> %f,%f,%f %f %zu,%zu,%zu \n", \
			obj->sp.x, obj->sp.y, obj->sp.z, obj->sp.diameter, obj->sp.r, obj->sp.g, obj->sp.b);
		else if (elem->type == PLANE)
			printf("PLANE\t\t=> %f,%f,%f %f,%f,%f %zu,%zu,%zu \n", \
			obj->pl.x, obj->pl.y, obj->pl.z, obj->pl.vec_x, obj->pl.vec_y, obj->pl.vec_z, obj->pl.r, obj->pl.g, obj->pl.b);
		else if (elem->type == CYLINDER)
			printf("CYLINDER\t=> %f,%f,%f %f,%f,%f %f %f %zu,%zu,%zu \n", \
			obj->cy.x, obj->cy.y, obj->cy.z, obj->cy.vec_x, obj->cy.vec_y, obj->cy.vec_z, obj->cy.diameter, obj->cy.height, obj->cy.r, obj->cy.g, obj->cy.b);
		elem = elem->next;
	}
}
