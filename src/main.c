/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/08/12 16:03:22 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	char		*path;
	t_list		*objects;

	if (ac != 2)
		return (1);
	path = av[1];
	objects = NULL;
	parser(path, &objects);
	ft_print_objects(&objects);
	
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
	
	return (0);
}
