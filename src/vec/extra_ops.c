/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 18:48:52 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// void	vec3_add_to_self(t_vec3 **vec, t_vec3 *new)
// {
// 	t_vec3	*tmp;

// 	if (new)
// 	{
// 		tmp = vec3_add((*vec), new);
// 		if (tmp)
// 		{
// 			free((*vec));
// 			*vec = tmp;
// 		}
// 	}
// }

// void	vec_multiply_to_self(double vec[3], double t)
// {
// 	tmp = vec3_multiply((*vec), t);
// 	if (tmp)
// 	{
// 		free((*vec));
// 		*vec = tmp;
// 	}
// }

// t_vec3	*vec3_ray_distance_to_point(t_vec3 *origin, t_vec3 *direction, double t)
// {
// 	t_vec3	*dist;
// 	t_vec3	*xyz;

// 	dist = vec3_multiply(direction, t);
// 	if (!dist)
// 		return (NULL);
// 	xyz = vec3_add(origin, dist);
// 	free(dist);
// 	if (!xyz)
// 		return (NULL);
// 	return (xyz);
// }
