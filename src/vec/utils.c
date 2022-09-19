/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 10:51:48 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	vec_set(double a, double b, double c, double (*vec)[3])
{
	(*vec)[0] = a;
	(*vec)[1] = b;
	(*vec)[2] = c;
}

void	vec_copy(double vec[3], double (*res)[3])
{
	vec_set(vec[0], vec[1], vec[2], res);
}

void	vec_ray_distance_to_point(double origin[3], double direction[3], \
													double t, double (*res)[3])
{
	double	dist[3];

	vec_multiply(direction, t, &dist);
	vec_add(origin, dist, res);
}

double	vec_distance_points(double pt1[3], double pt2[3])
{
	double	sub[3];
	double	res;

	vec_subtract(pt1, pt2, &sub);
	res = vec_len(sub);
	return (res);
}

void	vec_print(char *str, double vec[3])
{
	printf("%s\n", str);
	printf("/ %5.3f \\\n", vec[0]);
	printf("| %5.3f |\n", vec[1]);
	printf("\\ %5.3f /\n", vec[2]);
}
