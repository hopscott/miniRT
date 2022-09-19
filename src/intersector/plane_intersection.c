/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/19 13:17:22 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================================	*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/  	*/
/* minimal-ray-tracer-rendering-simple-shapes/					*/
/* ray-plane-and-ray-disk-intersection							*/
/* ============================================================	*/

void	sub_adjust_plane_norm(t_plane **plane, double inv_p_norm[3], \
															double r_or[3])
{
	double	p_norm_p1[3];
	double	p_norm_p2[3];
	double	distance1;
	double	distance2;

	vec_ray_distance_to_point((*plane)->xyz, (*plane)->norm, 1, &p_norm_p1);
	vec_ray_distance_to_point((*plane)->xyz, inv_p_norm, 1, &p_norm_p2);
	distance1 = vec_distance_points(r_or, p_norm_p1);
	distance2 = vec_distance_points(r_or, p_norm_p2);
	if (distance2 < distance1)
		vec_copy(inv_p_norm, &(*plane)->norm);
}

void	adjust_plane_norm(t_obj_lst *space_objs, double r_or[3])
{
	double		inv_p_norm[3];
	t_plane		*plane;
	t_object	*elem;

	while (space_objs)
	{
		if (space_objs->type == PLANE)
		{
			elem = (t_object *)(space_objs->content);
			plane = &(elem->pl);
			vec_multiply(plane->norm, -1, &inv_p_norm);
			sub_adjust_plane_norm(&plane, inv_p_norm, r_or);
		}
		space_objs = space_objs->next;
	}
}

int	plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit)
{
	double	p0[3];
	double	n[3];
	double	vec[3];

	vec_copy(plane->xyz, &p0);
	vec_copy(plane->norm, &n);
	vec_subtract(p0, ray->origin, &vec);
	hit->t = vec_dot(vec, n) / vec_dot(ray->direction, n);
	return (0);
}
