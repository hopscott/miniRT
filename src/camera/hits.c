/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/18 21:51:37 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
}

/* ============================================================= */
/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/ */
/* 3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */
/* ============================================================= */

void	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit)
{
	double		tmin;
	t_object	*obj;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		find_intersection(elem->type, ray, obj, hit);
		if ((hit->t >= 0.000001) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}
