/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/01 20:05:21 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_intersection(t_ray *ray, t_light *light, t_hit *hit)
{
	t_vec3	*vec;
	t_vec3	*xyz;

	xyz = vec3_init(light->x, light->y, light->z);
	vec = vec3_subtract(xyz, ray->origin);
	hit->t = vec3_dot(vec, ray->direction);
	free(xyz);
	free(vec);
}
