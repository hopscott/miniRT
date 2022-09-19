/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 10:16:02 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	vec_add(double vec1[3], double vec2[3], double (*res)[3])
{
	double	a;
	double	b;
	double	c;

	a = vec1[0] + vec2[0];
	b = vec1[1] + vec2[1];
	c = vec1[2] + vec2[2];
	vec_set(a, b, c, res);
}

void	vec_subtract(double vec1[3], double vec2[3], double (*res)[3])
{
	double	a;
	double	b;
	double	c;

	a = vec1[0] - vec2[0];
	b = vec1[1] - vec2[1];
	c = vec1[2] - vec2[2];
	vec_set(a, b, c, res);
}

void	vec_multiply(double vec[3], double n, double (*res)[3])
{
	double	a;
	double	b;
	double	c;

	a = vec[0] * n;
	b = vec[1] * n;
	c = vec[2] * n;
	vec_set(a, b, c, res);
}

void	vec_divide(double vec[3], double n, double (*res)[3])
{
	double	a;
	double	b;
	double	c;

	a = vec[0] / n;
	b = vec[1] / n;
	c = vec[2] / n;
	vec_set(a, b, c, res);
}

double	vec_dot(double vec1[3], double vec2[3])
{
	double	dot;

	dot = vec1[0] * vec2[0];
	dot += vec1[1] * vec2[1];
	dot += vec1[2] * vec2[2];
	return (dot);
}
