/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:08:30 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/06 16:10:29 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vec_matrix_multiply_bis(t_mat44 *mat, double old_vec[3], double w, \
		double (*res)[3])
{
	double	a;
	double	b;
	double	c;
	double	vec[3];

	get_new_norm(old_vec, &vec);
	if (mat)
	{
		a = (mat->a[0] * vec[0]) + (mat->b[0] * vec[1]) \
			+ (mat->c[0] * vec[2]) + (mat->d[0] * w);
		b = (mat->a[1] * vec[0]) + (mat->b[1] * vec[1]) \
			+ (mat->c[1] * vec[2]) + (mat->d[1] * w);
		c = (mat->a[2] * vec[0]) + (mat->b[2] * vec[1]) \
			+ (mat->c[2] * vec[2]) + (mat->d[2] * w);
		vec_set(a, b, c, res);
	}
}
