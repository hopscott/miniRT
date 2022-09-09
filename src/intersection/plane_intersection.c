/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/09 18:51:14 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection */

void	plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit)
{
	t_vec3	*p0;
	t_vec3	*n;
	t_vec3	*vec;

	p0 = plane->xyz;
	n = plane->norm;
	vec = vec3_subtract(p0, ray->origin);
	hit->t = vec3_dot(vec, n) / vec3_dot(ray->direction, n);
	free(vec);
}

/* https://math.stackexchange.com/questions/4402134/determining-plane-intersection-with-a-ray */

t_vec3	*plane_surface_normal(t_plane *plane, t_ray *ray)
{
	double	a;
	double	b;
	t_vec3	*vec;

	vec = vec3_subtract(plane->xyz, ray->origin);
	a = vec3_dot(vec, plane->norm);
	b = vec3_dot(ray->direction, plane->norm);
	free(vec);
	if (a < 0)
	{
		if (b < 0)
			return (vec3_multiply(plane->norm, -1));
		else
			return (vec3_copy(plane->norm));
	}
	else
	{
		if (b < 0)
			return (vec3_copy(plane->norm));
		else
			return (vec3_multiply(plane->norm, -1));
	}
}
