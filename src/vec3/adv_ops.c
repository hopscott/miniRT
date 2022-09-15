/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/09 18:16:46 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	vec3_dot(t_vec3 *vec1, t_vec3 *vec2)
{
	double	dot;

	dot = vec1->e[0] * vec2->e[0];
	dot += vec1->e[1] * vec2->e[1];
	dot += vec1->e[2] * vec2->e[2];
	return (dot);
}

double	vec3_lensq(t_vec3 *vec)
{
	double	lensq;

	lensq = vec->e[0] * vec->e[0];
	lensq += vec->e[1] * vec->e[1];
	lensq += vec->e[2] * vec->e[2];
	return (lensq);
}

double	vec3_len(t_vec3 *vec)
{
	return (sqrt(vec3_lensq(vec)));
}

t_vec3	*vec3_unit(t_vec3 *vec1, int to_free)
{
	t_vec3	*vec;
	double	a;
	double	b;
	double	c;
	double	len;

	if (!vec1)
		return (NULL);
	len = vec3_len(vec1);
	a = vec1->e[0] / len;
	b = vec1->e[1] / len;
	c = vec1->e[2] / len;
	if (to_free)
		free(vec1);
	vec = vec3_init(a, b, c);
	return (vec);
}

double	vec3_distance_points(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*sub;
	double	res;

	sub = vec3_subtract(vec1, vec2);
	res = vec3_len(sub);
	free(sub);
	return (res);
}
