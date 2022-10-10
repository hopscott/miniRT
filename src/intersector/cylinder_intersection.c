/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:38 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/10 11:07:54 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint8_t	new_dist(double dist, double r_or[3], double r_dir[3], t_cylinder *cy)
{
	double	cy_point[3];
	double	cy_cent_mid[3];
	double	dist_p_center;
	double	dist_max;

	vec_ray_distance_to_point(r_or, r_dir, dist, &cy_point);
	vec_ray_distance_to_point(cy->xyz, cy->norm, cy->height / 2, &cy_cent_mid);
	dist_p_center = vec_distance_points(cy_point, cy_cent_mid);
	dist_max = sqrt(pow(cy->height / 2, 2) + pow(cy->radius, 2));
	if (dist_p_center < dist_max)
		return (1);
	return (0);
}

double	sub_find_smallest(double new_dist1, double new_dist2, \
												double dists[2], int type)
{
	if (type == 1)
	{
		if (new_dist1)
			return (dists[0]);
		else if (new_dist2)
			return (dists[1]);
	}
	if (type == 2)
	{
		if (new_dist2)
			return (dists[1]);
		else if (new_dist1)
			return (dists[0]);
	}
	return (-1);
}

double	find_smallest_dist(double r_or[3], double r_dir[3], t_cylinder *cy, \
															double dab[3])
{
	double	dist1;
	double	dist2;
	double	new_dist1;
	double	new_dist2;
	double	dists[2];

	dist1 = (((-dab[2] + sqrt(dab[0])) / (2 * dab[1])));
	dist2 = ((-dab[2] - sqrt(dab[0])) / (2 * dab[1]));
	new_dist1 = new_dist(dist1, r_or, r_dir, cy);
	new_dist2 = new_dist(dist2, r_or, r_dir, cy);
	if (new_dist1 == -1 || new_dist2 == -1)
		return (-10);
	dists[0] = dist1;
	dists[1] = dist2;
	if (dist1 < dist2)
		return (sub_find_smallest(new_dist1, new_dist2, dists, 1));
	else
		return (sub_find_smallest(new_dist1, new_dist2, dists, 2));
	return (-1);
}

int	cy_intersection(t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	double	abc[3];
	double	rot_r_dir[3];
	double	discr;
	double	dab[3];

	vec_cross(ray->direction, cy->norm, &rot_r_dir);
	abc[0] = vec_dot(rot_r_dir, rot_r_dir);
	abc[1] = 2 * vec_dot(rot_r_dir, cy->cross_co_orient);
	abc[2] = vec_dot(cy->cross_co_orient, cy->cross_co_orient) \
												- pow(cy->radius, 2);
	discr = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discr < (double)0)
		hit->t = -1;
	vec_set(discr, abc[0], abc[1], &dab);
	hit->t = find_smallest_dist(ray->origin, ray->direction, cy, dab);
	if (hit->t == -10)
		return (1);
	return (0);
}

int	cy_intersection_lray(t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	double	abc[3];
	double	rot_r_dir[3];
	double	discr;
	double	dab[3];

	vec_cross(ray->direction, cy->norm, &rot_r_dir);
	abc[0] = vec_dot(rot_r_dir, rot_r_dir);
	abc[1] = 2 * vec_dot(rot_r_dir, cy->cross_lo_orient);
	abc[2] = vec_dot(cy->cross_lo_orient, cy->cross_lo_orient) \
												- pow(cy->radius, 2);
	discr = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discr < (double)0)
		hit->t = -1;
	vec_set(discr, abc[0], abc[1], &dab);
	hit->t = find_smallest_dist(ray->origin, ray->direction, cy, dab);
	if (hit->t == -10)
		return (1);
	return (0);
}
