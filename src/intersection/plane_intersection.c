/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/29 22:16:54 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection */

double	plane_intersection(t_vec3 *origin, t_vec3 *direction, t_plane *plane)
{
	double	t;
	t_vec3	*p0;
	t_vec3	*n;
	t_vec3	*vec;

	p0 = vec3_init(plane->x, plane->y, plane->z);
	n = vec3_init(plane->vec_x, plane->vec_y, plane->vec_z);
	vec = vec3_subtract(p0, origin);
	t = vec3_dot(vec, n) / vec3_dot(direction, n);
	free(p0);
	free(n);
	free(vec);
	return (t);
}

t_vec3	*plane_secondary_ray_origin(t_vec3 *origin, t_vec3 *direction, double t)
{
	t_vec3	*dist;
	t_vec3	*phit;

	dist = vec3_multiply(direction, t);
	phit = vec3_add(origin, dist);
	free(dist);
	return (phit);
}

/* https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector */

t_vec3	*plane_secondary_ray_direction(t_vec3 *origin, t_vec3 *direction, t_vec3 *normal)
{
	t_vec3	*dot;
	t_vec3	*cross;
	t_vec3	*mult;
	t_vec3	*reflection;

	dot = vec3_dot(direction, normal);
	cross = vec3_cross(dot, normal);
	mult = vec3_multiply(cross, 2);
	reflection = vec3_subtract(direction, mult);
	free(dot);
	free(cross);
	free(mult);
	return (reflection);
}
