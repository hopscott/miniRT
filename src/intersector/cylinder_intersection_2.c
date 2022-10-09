/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:19:59 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/09 20:22:53 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* ===================================================== */
/* https://stackoverflow.com/questions/36266357/		 */
/* how-can-i-compute-normal-on-the-surface-of-a-cylinder */
/* ===================================================== */

void	cylinder_surface_normal(t_cylinder *cy, double phit[3], \
														double (*norm)[3])
{
	double	t;
	double	dist[3];
	double	pt[3];

	vec_subtract(phit, cy->xyz, &dist);
	t = vec_dot(dist, cy->norm);
	vec_ray_distance_to_point(cy->xyz, cy->norm, t, &pt);
	vec_subtract(phit, pt, norm);
	vec_unit(*norm, norm);
}
