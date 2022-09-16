/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 18:46:16 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec_init(double a, double b, double c, double vec[3])
{
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
}

// t_vec3	*vec3_copy(t_vec3 *vec)
// {
// 	t_vec3	*new;

// 	new = vec3_init(vec->e[0], vec->e[1], vec->e[2]);
// 	return (new);
// }

// void	vec3_print(char *str, t_vec3 *vec)
// {
// 	printf("%s\n", str);
// 	printf("/ %f \\\n", vec->e[0]);
// 	printf("| %f |\n", vec->e[1]);
// 	printf("\\ %f /\n", vec->e[2]);
// }

// int	vec3_free_multi(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, int err)
// {
// 	if (v1)
// 		free(v1);
// 	if (v2)
// 		free(v2);
// 	if (v3)
// 		free(v3);
// 	return (err);
// }

// //just_for_testing_not_needed
// void	vec3_free_multi2(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3)
// {
// 	printf("ptr: %p\n", v2);
// 	if (v1)
// 		free(v1);
// 	if (v2)
// 	{
// 		printf("entered to v2\n");
// 		free(v2);
// 	}
// 	if (v3)
// 		free(v3);
// }
