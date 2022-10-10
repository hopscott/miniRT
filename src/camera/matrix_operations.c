/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/10/09 22:41:03 by omoudni          ###   ########.fr       */
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

void	mat_x_mat_utils(double (*col_to_fill)[3],
		t_mat44 *mat1, double col[3], int d)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (d)
			(*col_to_fill)[i] = mat1->a[i] * col[0]
				+ mat1->b[i] * col[1] + mat1->c[i] * col[2] + mat1->d[i];
		else
			(*col_to_fill)[i] = mat1->a[i] * col[0]
				+ mat1->b[i] * col[1] + mat1->c[i] * col[2];
		i++;
	}
}

t_mat44	*mat_x_mat(t_mat44 *mat1, t_mat44 *mat2, int to_free)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*ret;

	mat_x_mat_utils(&a, mat1, mat2->a, 0);
	mat_x_mat_utils(&b, mat1, mat2->b, 0);
	mat_x_mat_utils(&c, mat1, mat2->c, 0);
	mat_x_mat_utils(&d, mat1, mat2->d, 1);
	if (to_free)
	{
		free(mat1);
		free(mat2);
	}
	ret = mat44_init(a, b, c, d);
	return (ret);
}

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
