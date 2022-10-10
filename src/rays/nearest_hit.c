/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:59:37 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 11:20:31 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================================= */
/* Cylinder coded by Ouafae MOUDNI - issue with init_cy_params   */
/* needs to reset to light coordinate system when intersect lray */
/* ============================================================= */

void	find_intersection(int type, t_ray *ray, t_object *obj, t_hit *hit)
{
	if (type == LIGHT)
		light_intersection(ray, &obj->l, hit);
	else if (type == SPHERE)
		sphere_intersection(ray, &obj->sp, hit);
	else if (type == PLANE)
		plane_intersection(ray, &obj->pl, hit);
	else if (type == CYLINDER)
		cy_intersection(ray, &obj->cy, hit);
	else if (type == CYLINDER_L_RAY)
		cy_intersection_lray(ray, &obj->cy, hit);
}

/* ============================================================= */
/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/ */
/* 3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */
/* ============================================================= */

void	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit, \
														int ray_type)
{
	double		tmin;
	int			type;
	t_object	*obj;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		type = elem->type;
		if ((type == CYLINDER) && (ray_type == LIGHT))
			type = CYLINDER_L_RAY;
		obj = (t_object *)(elem->content);
		find_intersection(type, ray, obj, hit);
		if ((hit->t > EPSILON) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}
