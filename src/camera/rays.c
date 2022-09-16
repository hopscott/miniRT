/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 16:34:53 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ================================================ */
/* https://math.stackexchange.com/questions/13261/  */
/* how-to-get-a-reflection-vector 					*/
/* ================================================ */

t_vec3	*reflection_vector(t_vec3 *direction, t_vec3 *normal)
{
	double	dot;
	t_vec3	*vec;
	t_vec3	*reflection;

	dot = vec3_dot(direction, normal);
	vec = vec3_multiply(normal, (2 * dot));
	reflection = vec3_subtract(direction, vec);
	free(vec);
	return (reflection);
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
			return ('-');
		else if (elem->type == CYLINDER)
			return ('%');
	}
	return ('.');
}

int	hit_init(t_ray *ray, t_space *space, t_hit *hit)
{
	hit->phit = NULL;
	hit->shading = '.';
	hit->rgb = vec3_init(0, 0, 0);
	if (!hit->rgb)
		return (1);
	return (nearest_hit_object(ray, space->objects, hit));
}

size_t	cast_ray(t_ray *ray, t_space *space, char *chit, char *cshading)
{
	t_hit		hit;
	t_object	*obj;
	size_t		colour;

	if (hit_init(ray, space, &hit))
		return ((size_t)fatal_error_int(space));
	if (hit.nearest)
		obj = (t_object *)(hit.nearest->content);
	if ((hit.nearest) && (hit.nearest->type == LIGHT))
		vec3_add_to_self(&hit.rgb, obj->l.rgb);
	else if (hit.nearest)
	{
		hit.phit = vec3_ray_distance_to_point(ray->origin, \
				ray->direction, hit.t);
		if (!hit.phit)
			return ((size_t)fatal_error_int(space));
		shading(space, ray, &hit, obj);
	}
	else
		vec3_add_to_self(&hit.rgb, space->ambient->rgb);
	*chit = obj_to_char(hit.nearest);
	*cshading = hit.shading;
	colour = rgb_colour(hit.rgb);
	return ((size_t)vec3_free_multi(hit.phit, hit.rgb, NULL, colour));
}
