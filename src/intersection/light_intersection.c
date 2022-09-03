/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/03 21:01:36 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_intersection(t_ray *ray, t_light *light, t_hit *hit)
{
	t_vec3	*tmp;
	t_vec3	*dir;

	tmp = vec3_subtract(ray->origin, light->xyz);
	dir = vec3_unit(tmp, 0);
	if ((dir->e[0] != ray->direction->e[0]) && \
		(dir->e[1] != ray->direction->e[1]) && \
		(dir->e[2] != ray->direction->e[2]))
		hit->t = tmp->e[0] / ray->direction->e[0];
	else
		hit->t = INFINITY;
}
