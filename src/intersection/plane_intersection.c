/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/08 17:29:29 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection */

void	adjust_plane_norm(t_obj_lst *space_objs, t_vec3 *r_or)
{
	t_vec3	*ret;
	t_vec3	*p_norm_p1;
	t_vec3	*p_norm_p2;
	t_vec3	*inv_p_norm;
	double	distance1;
	double	distance2;
	t_plane	*plane;
	t_object	*elem;
	//	printf("p_norm's coordinates are: %f, %f, %f\n", plane->norm->e[0], plane->norm->e[1], plane->norm->e[2]);
	while (space_objs)
	{
		if (space_objs->type == PLANE)
		{
			elem = (t_object *)(space_objs->content);
			plane = &(elem->pl);
			inv_p_norm = vec3_multiply(plane->norm, -1);
			p_norm_p1 = vec_from_or_vec_len(plane->xyz, plane->norm, 1);
			p_norm_p2 = vec_from_or_vec_len(plane->xyz, inv_p_norm, 1);
			distance1 = vec3_distance_points(r_or, p_norm_p1);
			//			printf("dist1: %f\n", distance1);
			//			printf("p_norm's coordinates are: %f, %f, %f\n", plane->norm->e[0], plane->norm->e[1], plane->norm->e[2]);
			distance2 = vec3_distance_points(r_or, p_norm_p2);
			//			printf("dist2: %f\n", distance2);
			if (distance2 < distance1)
			{
		//		printf("x: %f, y: %f, z: %f\n", plane->xyz->e[0], plane->xyz->e[1], plane->xyz->e[2]);
		//		printf("n_x: %f, n_y: %f, n_z: %f\n", plane->norm->e[0], plane->norm->e[1], plane->norm->e[2]);
				plane->norm = vec3_copy(inv_p_norm);
			}
		}
		space_objs = space_objs->next;
	}
}

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

/* https://math.stackexchange.com/questions/4402134/determining-plane-intersection-with-a-ray */
/*
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
*/
