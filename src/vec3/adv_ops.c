/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/08/12 16:03:49 by swillis          ###   ########.fr       */
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

t_vec3	*vec3_cross(t_vec3 *vec1, t_vec3 *vec2)
{
	t_vec3	*vec;
	double	a;
	double	b;
	double	c;

	a = (vec1->e[1] * vec2->e[2]) - (vec1->e[2] * vec2->e[1]);
	b = (vec1->e[2] * vec2->e[0]) - (vec1->e[0] * vec2->e[2]);
	c = (vec1->e[0] * vec2->e[1]) - (vec1->e[1] * vec2->e[0]);
	vec = vec3_init(a, b, c);
	return (vec);
}

t_vec3	*vec3_unit(t_vec3 *vec1)
{
	t_vec3	*vec;
	double	a;
	double	b;
	double	c;
	double	len;

	len = vec3_len(vec1);
	a = vec1->e[0] / len;
	b = vec1->e[1] / len;
	c = vec1->e[2] / len;
	vec = vec3_init(a, b, c);
	return (vec);
}

void	vec3_print(t_vec3 *vec)
{
	printf("/ %f \\\n", vec->e[0]); 
	printf("| %f |\n", vec->e[1]);
	printf("\\ %f /\n", vec->e[2]);
}

