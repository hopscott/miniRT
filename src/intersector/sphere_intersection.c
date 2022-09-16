/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/16 17:45:36 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_c_dscr(double pxyz[3], double cxyz[3], t_sphere *sp, double *c)
{
	*c = pxyz[0] * pxyz[0] - 2 * pxyz[0] * cxyz[0] + cxyz[0] * cxyz[0] \
		+ pxyz[1] * pxyz[1] - 2 * pxyz[1] * cxyz[1] + cxyz[1] * cxyz[1] \
		+ pxyz[2] * pxyz[2] - 2 * pxyz[2] * cxyz[2] + cxyz[2] * cxyz[2] \
		- pow(sp->diameter / 2, 2);
}

int	sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	*abc_dsc;
	double	discriminant;

	abc_dsc = get_dscr(ray, sp);
	if (!abc_dsc)
		return (1);
	discriminant = abc_dsc[2];
	if (discriminant < 0)
		hit->t = -1;
	else
		hit->t = get_short_dist(discriminant, abc_dsc[0], abc_dsc[1]);
	free(abc_dsc);
	return (0);
}

t_vec3	*sphere_surface_normal(t_ray *ray, t_sphere *sphere, t_vec3 *phit)
{
	t_vec3	*tmp;
	t_vec3	*normal;

	if (vec3_distance_points(ray->origin, sphere->xyz) < sphere->diameter / 2)
		tmp = vec3_subtract(sphere->xyz, phit);
	else
		tmp = vec3_subtract(phit, sphere->xyz);
	if (!tmp)
		return (NULL);
	normal = vec3_unit(tmp, 1);
	if (!normal)
		return (free(tmp), NULL);
	return (normal);
}
