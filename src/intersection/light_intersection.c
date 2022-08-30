/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/31 00:52:48 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_intersection(t_ray *ray, t_light_lst *elem, t_hit *hit)
{
	t_vec3	*vec;
	t_vec3	*xyz;

	xyz = vec3_init(elem->light.x, elem->light.y, elem->light.z);
	vec = vec3_subtract(xyz, ray->origin);
	hit->t = vec3_dot(vec, ray->direction);
	free(xyz);
	free(vec);
}
