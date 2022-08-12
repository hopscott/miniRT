/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/08/12 15:43:57 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

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

t_vec3	*vec3_init(double a, double b, double c)
{
	t_vec3	*vec;

	vec = malloc(sizeof(t_vec3));
	if (!vec)
		return (NULL);
	vec->e[0] = a;
	vec->e[1] = b;
	vec->e[2] = c;
	return (vec);
}
