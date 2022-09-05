/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/05 18:34:35 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_intersection(t_ray *ray, t_light *light, t_hit *hit)
{
	t_vec3	*tmp;
	t_vec3	*dir;

	tmp = vec3_subtract(light->xyz, ray->origin);
	dir = vec3_unit(tmp, 0);
	if (vec3_dot(dir, ray->direction) == 1)
		hit->t = tmp->e[0] / dir->e[0];
	else
		hit->t = INFINITY;
	free(tmp);
	free(dir);
}
