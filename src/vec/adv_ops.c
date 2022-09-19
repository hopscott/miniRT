/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:56:59 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 09:59:44 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

double	vec_lensq(double vec[3])
{
	double	lensq;

	lensq = vec[0] * vec[0];
	lensq += vec[1] * vec[1];
	lensq += vec[2] * vec[2];
	return (lensq);
}

double	vec_len(double vec[3])
{
	return (sqrt(vec_lensq(vec)));
}

void	vec_unit(double vec[3], double (*res)[3])
{
	double	a;
	double	b;
	double	c;
	double	len;

	len = vec_len(vec);
	a = vec[0] / len;
	b = vec[1] / len;
	c = vec[2] / len;
	vec_set(a, b, c, res);
}

void	vec_cross(double vec1[3], double vec2[3], double (*res)[3])
{
	double	a;
	double	b;
	double	c;

	a = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
	b = (vec1[2] * vec2[0]) - (vec1[0] * vec2[2]);
	c = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
	vec_set(a, b, c, res);
}
