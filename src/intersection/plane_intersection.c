/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/31 17:29:43 by swillis          ###   ########.fr       */
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

/* https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector */

t_vec3	*plane_secondary_ray_direction(t_vec3 *direction, t_vec3 *normal)
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
