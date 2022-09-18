/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/18 17:25:40 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================================	*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/  	*/
/* minimal-ray-tracer-rendering-simple-shapes/					*/
/* ray-plane-and-ray-disk-intersection							*/
/* ============================================================	*/

void	free_2_vec3(t_vec3 **a, t_vec3 **b)
{
	if (*a)
		free(*a);
	if (*b)
		free(*b);
}

int	sub_adjust_plane_norm(t_plane **plane, t_vec3 *inv_p_norm, t_vec3 *r_or)
{
	t_vec3	*p_norm_p1;
	t_vec3	*p_norm_p2;
	double	distance1;
	double	distance2;

	p_norm_p1 = vec3_ray_distance_to_point((*plane)->xyz, (*plane)->norm, 1);
	if (!p_norm_p1)
		return (1);
	p_norm_p2 = vec3_ray_distance_to_point((*plane)->xyz, inv_p_norm, 1);
	if (!p_norm_p2)
		return (free(p_norm_p1), 1);
	distance1 = vec3_distance_points(r_or, p_norm_p1);
	distance2 = vec3_distance_points(r_or, p_norm_p2);
	free_2_vec3(&p_norm_p1, &p_norm_p2);
	if (distance2 < distance1)
	{
		free((*plane)->norm);
		(*plane)->norm = vec3_copy(inv_p_norm);
	}
	if (!(*plane)->norm)
		return (1);
	return (0);
}

int	adjust_plane_norm(t_space *space, t_obj_lst *space_objs, t_vec3 *r_or)
{
	t_vec3		*inv_p_norm;
	t_plane		*plane;
	t_object	*elem;

	while (space_objs)
	{
		if (space_objs->type == PLANE)
		{
			elem = (t_object *)(space_objs->content);
			plane = &(elem->pl);
			inv_p_norm = vec3_multiply(plane->norm, -1);
			if (!inv_p_norm)
				return (1);
			if (sub_adjust_plane_norm(&plane, inv_p_norm, r_or))
				return (free(inv_p_norm), 1);
			printf("%f %f %f\n", plane->norm->e[0], plane->norm->e[1], plane->norm->e[2]);
			get_e1_e2(space, plane);
			free(inv_p_norm);
		}
		space_objs = space_objs->next;
	}
	return (0);
}

int	plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit)
{
	t_vec3	*p0;
	t_vec3	*n;
	t_vec3	*vec;

	p0 = plane->xyz;
	n = plane->norm;
	vec = vec3_subtract(p0, ray->origin);
	if (!vec)
		return (1);
	hit->t = vec3_dot(vec, n) / vec3_dot(ray->direction, n);
	free(vec);
	return (0);
}
