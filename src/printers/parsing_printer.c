/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 16:03:59 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_sphere *sp)
{
	printf("  o   SPHERE   ");
	printf("|");
	printf(" (%5.1lf,%5.1lf,%5.1lf) ", sp->x, sp->y, sp->z);
	printf("|");
	printf("                     ");
	printf("|");
	printf(" (%3zu,%3zu,%3zu) ", sp->r, sp->g, sp->b);
	printf("|");
	printf("  %5.1f   ", sp->diameter);
	printf("|");
	printf("        ");
	printf("|");
	printf("            ");
	printf("|");
	printf("    ");
	printf("\n");
}

void	print_plane(t_plane *pl)
{
	printf(" [X]  PLANE    ");
	printf("|");
	printf(" (%5.1lf,%5.1lf,%5.1lf) ", pl->x, pl->y, pl->z);
	printf("|");
	printf(" (%5.2f,%5.2f,%5.2f) ", pl->vec_x, pl->vec_y, pl->vec_z);
	printf("|");
	printf(" (%3zu,%3zu,%3zu) ", pl->r, pl->g, pl->b);
	printf("|");
	printf("          ");
	printf("|");
	printf("        ");
	printf("|");
	printf("            ");
	printf("|");
	printf("    ");
	printf("\n");
}

void	print_cylinder(t_cylinder *cy)
{
	printf(" o=o  CYLINDER ");
	printf("|");
	printf(" (%5.1lf,%5.1lf,%5.1lf) ", cy->x, cy->y, cy->z);
	printf("|");
	printf(" (%5.2f,%5.2f,%5.2f) ", cy->vec_x, cy->vec_y, cy->vec_z);
	printf("|");
	printf(" (%3zu,%3zu,%3zu) ", cy->r, cy->g, cy->b);
	printf("|");
	printf("  %5.1f   ", cy->diameter);
	printf("|");
	printf(" %5.1f  ", cy->height);
	printf("|");
	printf("            ");
	printf("|");
	printf("    ");
	printf("\n");
}

void	print_space(t_space *space)
{
	t_obj_lst		*elem;
	t_object		*obj;

	print_columns();
	print_ambient(space->ambient);
	print_camera(space->camera);
	elem = space->objects;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == LIGHT)
			print_light(&obj->l);
		else if (elem->type == SPHERE)
			print_sphere(&obj->sp);
		else if (elem->type == PLANE)
			print_plane(&obj->pl);
		else if (elem->type == CYLINDER)
			print_cylinder(&obj->cy);
		elem = elem->next;
	}
}
