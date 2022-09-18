/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/18 21:19:56 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/					 */
/* mathematics-physics-for-computer-graphics/lookat-function */

t_mat44	*mat44_init(double a[3], double b[3], double c[3], double d[3])
{
	t_mat44	*mat;
	int		i;

	mat = malloc(sizeof(t_mat44));
	if (!mat)
		return (NULL);
	i = -1;
	while (++i < 3)
		mat->a[i] = a[i];
	mat->a[i] = 0;
	i = -1;
	while (++i < 3)
		mat->b[i] = b[i];
	mat->b[i] = 0;
	i = -1;
	while (++i < 3)
		mat->c[i] = c[i];
	mat->c[i] = 0;
	i = -1;
	while (++i < 3)
		mat->d[i] = d[i];
	mat->d[i] = 1;
	return (mat);
}

t_mat44	*camera_lookat(t_camera *cam)
{
	double	fwd[3];
	double	arb[3];
	double	right[3];
	double	up[3];
	double	coord[3];

	if (!cam)
		return (NULL);
	vec_copy(cam->norm, &fwd);
	vec_set(0, 1, 0, &arb);
	vec_unit(arb, &arb);
	vec_cross(arb, fwd, &right);
	vec_unit(right, &right);
	vec_cross(fwd, right, &up);
	vec_unit(up, &up);
	vec_set(-vec_dot(right, cam->xyz), -vec_dot(up, cam->xyz), \
										-vec_dot(fwd, cam->xyz), &coord);
	return (mat44_init(right, up, fwd, coord));
}

/* https://math.stackexchange.com/questions/89621/how-to-multiply-vector- */
/* 3-with-4by4-matrix-more-precisely-position-transformat 				  */

void	vec_matrix_multiply(t_mat44 *mat, double vec[3], double w, \
															double (*res)[3])
{
	double	a;
	double	b;
	double	c;

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
