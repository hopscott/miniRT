/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/09 16:51:00 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_short_dist(double discriminant, double a, double b)
{
	double	t1;
	double	t2;

	t1 = (-1 * b - sqrt(discriminant)) / (2 * a);
	t2 = (-1 * b + sqrt(discriminant)) / (2 * a);
	if ((t1 > 0) && (t1 <= t2))
		return (t1);
	return (t2);
}

/* ============================================================== */
/* https://stackoverflow.com/questions/5883169/					  */
/* intersection-between-a-line-and-a-sphere						  */
/* ============================================================== */
/* https://raytracing.github.io/books/RayTracingInOneWeekend.html */
/* #addingasphere/ray-sphereintersection						  */
/* ============================================================== */

void	sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	oc[3];
	double	abc[3];
	double	discriminant;

	vec_subtract(ray->origin, sp->xyz, &oc);
	vec_set(vec_dot(ray->direction, ray->direction), \
			2 * vec_dot(oc, ray->direction), \
			vec_dot(oc, oc) - pow(sp->diameter / 2, 2), \
			&abc);
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		hit->t = -1;
	else
		hit->t = get_short_dist(discriminant, abc[0], abc[1]);
}

void	sphere_surface_normal(t_ray *ray, t_sphere *sphere, double phit[3], \
															double (*norm)[3])
{
	if (vec_distance_points(ray->origin, sphere->xyz) < sphere->diameter / 2)
		vec_subtract(sphere->xyz, phit, norm);
	else
		vec_subtract(phit, sphere->xyz, norm);
	vec_unit(*norm, norm);
}
