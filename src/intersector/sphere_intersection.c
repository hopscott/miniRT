/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/18 21:56:13 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================ */
/* https://stackoverflow.com/questions/5883169/ */
/* intersection-between-a-line-and-a-sphere		*/
/* ============================================ */

void	calc_c_dscr(double pxyz[3], double cxyz[3], t_sphere *sp, double *c)
{
	*c = pxyz[0] * pxyz[0] - 2 * pxyz[0] * cxyz[0] + cxyz[0] * cxyz[0] \
		+ pxyz[1] * pxyz[1] - 2 * pxyz[1] * cxyz[1] + cxyz[1] * cxyz[1] \
		+ pxyz[2] * pxyz[2] - 2 * pxyz[2] * cxyz[2] + cxyz[2] * cxyz[2] \
		- pow(sp->diameter / 2, 2);
}

void	get_dscr(t_ray *ray, t_sphere *sp, double (*ab_dsc)[3])
{
	double	s_center[3];
	double	abc[3];
	double	vec_substr[3];

	vec_set(sp->x, sp->y, sp->z, &s_center);
	vec_subtract(ray->origin, s_center, &vec_substr);
	abc[0] = vec_dot(ray->direction, ray->direction);
	abc[1] = 2 * vec_dot(vec_substr, ray->direction);
	calc_c_dscr(ray->origin, s_center, sp, &(abc[2]));
	vec_subtract(ray->origin, s_center, &vec_substr);
	vec_set(vec_dot(ray->direction, ray->direction),\
			2 * vec_dot(vec_substr, ray->direction),\
			abc[1] * abc[1] - 4 * abc[0] * abc[2],  \
			ab_dsc);
}

double	get_short_dist(double discriminant, double a, double b)
{
	double	t1;
	double	t2;

	t1 = (-1 * b - sqrt(discriminant)) / (2 * a);
	t2 = (-1 * b + sqrt(discriminant)) / (2 * a);
	if (t1 <= t2)
		return (t1);
	return (t2);
}

void	sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	abc_dsc[3];
	double	discriminant;

	get_dscr(ray, sp, &abc_dsc);
	discriminant = abc_dsc[2];
	if (discriminant < 0)
		hit->t = -1;
	else
		hit->t = get_short_dist(discriminant, abc_dsc[0], abc_dsc[1]);
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
