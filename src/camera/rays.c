/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/05 16:39:27 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ================================================ */
/* https://math.stackexchange.com/questions/13261/  */
/* how-to-get-a-reflection-vector 					*/
/* ================================================ */

void	reflection_vector(double direction[3], double norm[3], double (*res)[3])
{
	double	dot;
	double	vec[3];

	dot = vec_dot(direction, norm);
	vec_multiply(norm, (2 * dot), &vec);
	vec_subtract(direction, vec, res);
}

char	obj_to_char(t_obj_lst *elem)
{
	if (elem)
	{
		if (elem->type == LIGHT)
			return ('@');
		else if (elem->type == SPHERE)
			return ('o');
		else if (elem->type == PLANE)
			return ('/');
		else if (elem->type == CYLINDER)
			return ('%');
	}
	return ('.');
}

size_t	cast_ray(t_ray *ray, t_space *space, char *chit, char *cshading)
{
	t_hit		hit;
	t_object	*obj;

	hit.shading = '.';
	vec_set(0, 0, 0, &hit.rgb);
	nearest_hit_object(ray, space->objects, &hit);
	if (hit.nearest)
		obj = (t_object *)(hit.nearest->content);
	if ((hit.nearest) && (hit.nearest->type == LIGHT))
		vec_add(hit.rgb, obj->l.rgb, &hit.rgb);
	else if (hit.nearest)
	{
		vec_ray_distance_to_point(ray->origin, ray->direction, hit.t, \
																&hit.phit);
		shading(space, ray, &hit, obj);
	}
	else
		vec_add(hit.rgb, space->ambient->rgb, &hit.rgb);
	*chit = obj_to_char(hit.nearest);
	*cshading = hit.shading;
	return (rgb_colour(hit.rgb));
}
