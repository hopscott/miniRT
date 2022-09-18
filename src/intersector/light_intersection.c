/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/18 19:55:34 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	light_intersection(t_ray *ray, t_light *light, t_hit *hit)
{
	double	dist[3];
	double	dir[3];

	vec_subtract(light->xyz, ray->origin, &dist);
	vec_unit(dist, &dir);
	if (vec_dot(dir, ray->direction) > 0.99999)
		hit->t = dist[0] / dir[0];
	else
		hit->t = INFINITY;
	return (0);
}
