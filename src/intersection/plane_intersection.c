/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/02 18:05:04 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection */

void	plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit)
{
	t_vec3	*p0;
	t_vec3	*n;
	t_vec3	*vec;

	p0 = vec3_init(plane->x, plane->y, plane->z);
	n = vec3_init(plane->vec_x, plane->vec_y, plane->vec_z);
	vec = vec3_subtract(p0, ray->origin);
	hit->t = vec3_dot(vec, n) / vec3_dot(ray->direction, n);
	free(p0);
	free(n);
	free(vec);
}

t_vec3	*plane_surface_normal(t_plane *plane, t_vec3 *direction)
{
	t_vec3	*tmp;
	t_vec3	*normal;

	tmp = vec3_subtract(phit, sphere->xyz);
	normal = vec3_unit(tmp);
	free(tmp);
	return (normal);
}
