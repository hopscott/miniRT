/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nearest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/09 16:58:29 by swillis          ###   ########.fr       */
=======
/*   Updated: 2022/10/10 02:28:20 by omoudni          ###   ########.fr       */
>>>>>>> 1c8b2aa1c65cae869ca1c5358a5b2ec51af33269
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

void	find_intersection_2(int type, t_ray *ray, t_object *obj, t_hit *hit)
{
	if (type == LIGHT)
		light_intersection(ray, &obj->l, hit);
	else if (type == SPHERE)
		sphere_intersection(ray, &obj->sp, hit);
	else if (type == PLANE)
		plane_intersection(ray, &obj->pl, hit);
	else if (type == CYLINDER)
		cy_intersection_2(ray, &obj->cy, hit);
}

/* ============================================================= */
/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/ */
/* 3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */
/* ============================================================= */

void	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit, int i)
{
	double		tmin;
	t_object	*obj;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (i == 1)
			find_intersection(elem->type, ray, obj, hit);
		else
			find_intersection_2(elem->type, ray, obj, hit);
		if ((hit->t > EPSILON) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}
