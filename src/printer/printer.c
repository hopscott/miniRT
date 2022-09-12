/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 14:35:28 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_space(t_space *space)
{
	t_obj_lst		*elem;
	t_object		*obj;

	printf("\n~~~~ Space Layout ~~~~\n\n");
	printf("##### AMBIENT\t=> brightness(%.1f)\t\t\t\t\t\t\t\trgb(%zu,%zu,%zu) \n", space->ambient->lighting_ratio, space->ambient->r, space->ambient->g, space->ambient->b);
	printf("-<[0] CAMERA\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tfov(%zu) \n", space->camera->x, space->camera->y, space->camera->z, space->camera->vec_x, space->camera->vec_y, space->camera->vec_z, space->camera->fov);
	elem = space->objects;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == LIGHT)
			printf("((*)) LIGHT\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tbrightness(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", obj->l.x, obj->l.y, obj->l.z, obj->l.brightness_ratio, obj->l.r, obj->l.g, obj->l.b);
		else if (elem->type == SPHERE)
			printf("  o   SPHERE\t=> xyz(%.1f,%.1f,%.1f)\t\t\t\tdiameter(%.1f)\t\t\trgb(%zu,%zu,%zu) \n", obj->sp.x, obj->sp.y, obj->sp.z, obj->sp.diameter, obj->sp.r, obj->sp.g, obj->sp.b);
		else if (elem->type == PLANE)
			printf(" [X]  PLANE\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\t\t\t\t\trgb(%zu,%zu,%zu) \n", obj->pl.x, obj->pl.y, obj->pl.z, obj->pl.vec_x, obj->pl.vec_y, obj->pl.vec_z, obj->pl.r, obj->pl.g, obj->pl.b);
		else if (elem->type == CYLINDER)
			printf(" o=o  CYLINDER\t=> xyz(%.1f,%.1f,%.1f)\tdir(%.1f,%.1f,%.1f)\tdiameter(%.1f) height(%.1f)\trgb(%zu,%zu,%zu) \n", obj->cy.x, obj->cy.y, obj->cy.z, obj->cy.vec_x, obj->cy.vec_y, obj->cy.vec_z, obj->cy.diameter, obj->cy.height, obj->cy.r, obj->cy.g, obj->cy.b);
		elem = elem->next;
	}
}
