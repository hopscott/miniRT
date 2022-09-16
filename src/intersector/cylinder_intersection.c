/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:38 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/15 20:19:01 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint8_t	new_dist(double dist, t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy)
{
	t_vec3	*cy_point;
	t_vec3	*cy_center_middle;
	double	dist_p_center;
	double	dist_max;

	cy_point = vec3_ray_distance_to_point(r_or, r_dir, dist);
	if (!cy_point)
		return (-10);
	cy_center_middle = vec3_ray_distance_to_point(cy->xyz, cy->norm, cy->height / 2);
	if (!cy_center_middle)
		return (free(cy_point), -1);
	dist_p_center = vec3_distance_points(cy_point, cy_center_middle);
	dist_max = sqrt(pow(cy->height / 2, 2) + pow(cy->radius, 2));
	free(cy_point);
	free(cy_center_middle);
	if (dist_p_center < dist_max)
		return (1);
	return (0);
}

double	sub_find_smallest(double new_dist1, double new_dist2, double dists[2], int type)
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

double	find_smallest_dist(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy, double discr, double a, double b)
{
	double	dist1;
	double	dist2;
	double	new_dist1;
	double	new_dist2;
	double	dists[2];

	dist1 = (((- b + sqrt(discr)) / (2 * a)));
	dist2 = ((- b - sqrt(discr)) / (2 * a));
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
	t_vec3	*rot_r_dir;
	double	discr;

	rot_r_dir = vec3_cross(ray->direction, cy->norm);
	if (!rot_r_dir)
		return (1);
	abc[0] = vec3_dot(rot_r_dir, rot_r_dir);
	abc[1] = 2 * vec3_dot(rot_r_dir, cy->cross_co_orient);
	abc[2] = vec3_dot(cy->cross_co_orient, cy->cross_co_orient) - pow(cy->radius, 2);
	discr = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discr < 0)
		hit->t = -1;
	hit->t = find_smallest_dist(ray->origin, ray->direction, cy, discr, abc[0], abc[1]);
	if (hit->t == -10)
		return (1);
	free(rot_r_dir);
	return (0);
}

t_vec3	*cylinder_surface_normal(t_cylinder * cy, t_vec3 *phit)
{
	double	t;
	t_vec3	*pt;
	t_vec3	*surface_normal;
	t_vec3	*tmp1;
	t_vec3	*tmp2;

	tmp1 = vec3_subtract(phit, cy->xyz);
	if (!tmp1)
		return (NULL);
    t = vec3_dot(tmp1, cy->norm);
    pt = vec3_ray_distance_to_point(cy->xyz, cy->norm, t);
	if (!pt)
		return (free(tmp1), NULL);
	free(tmp1);
	tmp2 = vec3_subtract(phit, pt);
	free(pt);
	if (!tmp2)
		return (free(pt), NULL);
    surface_normal = vec3_unit(tmp2, 1);
	return (surface_normal);
}
