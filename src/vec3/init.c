/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/02 23:35:35 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

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

void	vec3_print(t_vec3 *vec)
{
	printf("/ %f \\\n", vec->e[0]);
	printf("| %f |\n", vec->e[1]);
	printf("\\ %f /\n", vec->e[2]);
}

void	vec3_free_multi(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3)
{
	if (v1)
		free(v1);
	if (v2)
		free(v2);
	if (v3)
		free(v3);
}

t_vec3	*vec3_copy(t_vec3 *vec)
{
	t_vec3	*new;

	new = vec3_init(vec->e[0], vec->e[1], vec->e[2]);
	return (new);
}

void	vec3_add_to_self(t_vec3 **vec, t_vec3 *new)
{
	t_vec3	*tmp;

	tmp = vec3_add((*vec), new);
	free((*vec));
	*vec = tmp;
}

/*
	t_vec3 *v1 = vec3_init(1, 2, 3);
	t_vec3 *v2 = vec3_init(30, 20, 10);
	
	printf("CROSS\n");
	vec3_print(vec3_cross(v1, v2));
	printf("ADD\n");
	vec3_print(vec3_add(v1, v2));
	printf("SUBTRACT\n");
	vec3_print(vec3_subtract(v1, v2));
	printf("DIVIDE\n");
	vec3_print(vec3_divide(v1, 3));
	printf("MULTIPLY\n");
	vec3_print(vec3_multiply(v1, 3));
	printf("DOT\n");
	printf("%f\n", vec3_dot(v1, v2));
*/
