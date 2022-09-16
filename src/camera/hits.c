/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 16:43:34 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_intersection(int type, t_ray *ray, t_object *obj, t_hit *hit)
{
	int	err;

	err = 0;
	if (type == LIGHT)
		err = light_intersection(ray, &obj->l, hit);
	else if (type == SPHERE)
		err = sphere_intersection(ray, &obj->sp, hit);
	else if (type == PLANE)
		err = plane_intersection(ray, &obj->pl, hit);
	else if (type == CYLINDER)
		err = cy_intersection(ray, &obj->cy, hit);
	return (err);
}

/* ============================================================= */
/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/ */
/* 3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */
/* ============================================================= */

int	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit)
{
	double		tmin;
	t_object	*obj;
	int			err;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		err = find_intersection(elem->type, ray, obj, hit);
		if (err)
			return (err);
		if ((hit->t >= 0.000001) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
	return (err);
}
