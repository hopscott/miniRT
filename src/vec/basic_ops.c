/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 18:49:54 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// t_vec3	*vec3_add(t_vec3 *vec1, t_vec3 *vec2)
// {
// 	t_vec3	*vec;
// 	double	a;
// 	double	b;
// 	double	c;

// 	a = vec1->e[0] + vec2->e[0];
// 	b = vec1->e[1] + vec2->e[1];
// 	c = vec1->e[2] + vec2->e[2];
// 	vec = vec3_init(a, b, c);
// 	return (vec);
// }

// t_vec3	*vec3_subtract(t_vec3 *vec1, t_vec3 *vec2)
// {
// 	t_vec3	*vec;
// 	double	a;
// 	double	b;
// 	double	c;

// 	a = vec1->e[0] - vec2->e[0];
// 	b = vec1->e[1] - vec2->e[1];
// 	c = vec1->e[2] - vec2->e[2];
// 	vec = vec3_init(a, b, c);
// 	return (vec);
// }

t_vec3	*vec_multiply(double vec[3], double n)
{
	vec[0] *= n;
	vec[1] *= n;
	vec[2] *= n;
}

// t_vec3	*vec3_divide(t_vec3 *vec1, double n)
// {
// 	t_vec3	*vec;
// 	double	a;
// 	double	b;
// 	double	c;

// 	a = vec1->e[0];
// 	b = vec1->e[1];
// 	c = vec1->e[2];
// 	if (n != 0)
// 	{
// 		a /= n;
// 		b /= n;
// 		c /= n;
// 	}
// 	else
// 		printf("Vec3 Error - Dividing by 0\n");
// 	vec = vec3_init(a, b, c);
// 	return (vec);
// }

// t_vec3	*vec3_cross(t_vec3 *vec1, t_vec3 *vec2)
// {
// 	t_vec3	*vec;
// 	double	a;
// 	double	b;
// 	double	c;

// 	a = (vec1->e[1] * vec2->e[2]) - (vec1->e[2] * vec2->e[1]);
// 	b = (vec1->e[2] * vec2->e[0]) - (vec1->e[0] * vec2->e[2]);
// 	c = (vec1->e[0] * vec2->e[1]) - (vec1->e[1] * vec2->e[0]);
// 	vec = vec3_init(a, b, c);
// 	return (vec);
// }
