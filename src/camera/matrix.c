/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/05 23:42:12 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function */

t_mat44	*mat44_init(t_vec3 *a, t_vec3 *b, t_vec3 *c, t_vec3 *d)
{
	t_mat44	*mat;
	int		i;

	mat = malloc(sizeof(t_mat44));
	if (!mat)
		return (NULL);
	i = -1;
	while (++i < 3)
		mat->a[i] = a->e[i];
	mat->a[i] = 0;
	i = -1;
	while (++i < 3)
		mat->b[i] = b->e[i];
	mat->b[i] = 0;
	i = -1;
	while (++i < 3)
		mat->c[i] = c->e[i];
	mat->c[i] = 0;
	i = -1;
	while (++i < 3)
		mat->d[i] = d->e[i];
	mat->d[i] = 1;
	return (mat);
}

// t_mat44	*lookat(t_vec3 *pt_from, t_vec3 *pt_to)
// {
// 	t_vec3	*fwd;
// 	t_vec3	*right;
// 	t_vec3	*up;
// 	t_mat44	*mat;

// 	fwd = vec3_unit(vec3_subtract(pt_to, pt_from));
// 	if (!fwd)
// 		return (NULL);
// 	right = vec3_cross(vec3_unit(vec3_init(0, 1, 0)), fwd);
// 	if (!right)
// 	{
// 		free(fwd);
// 		return (NULL);
// 	}
// 	up = vec3_cross(fwd, right);
// 	if (!up)
// 	{
// 		free(fwd);
// 		free(right);
// 		return (NULL);
// 	}
// 	mat = mat44_init(right, up, fwd, pt_from);
// 	free(fwd);
// 	free(right);
// 	free(up);
// 	return (mat);
// }

t_mat44	*camera_lookat_utils(t_vec3 *fwd, t_vec3 *old_coord, t_vec3 *arb)
{
	t_vec3	*right;
	t_vec3	*up;
	t_mat44	*mat;
	t_vec3	*coord;
	t_vec3	*tmp;

	tmp = vec3_cross(arb, fwd);
	right = vec3_unit(tmp, 1);
	if (!right)
		return (NULL);

	tmp = vec3_cross(fwd, right);
	up = vec3_unit(tmp, 1);
	if (!up)
	{
		free(right);
		return (NULL);
	}
	coord = vec3_init((-1) * vec3_dot(right, old_coord), (-1) * vec3_dot(up, old_coord), (-1) *vec3_dot(fwd, old_coord));
	mat = mat44_init(right, up, fwd, coord);
	free(right);
	free(up);
	return (mat);
}

t_mat44	*camera_lookat(t_camera *cam)
{
	t_vec3	*fwd;
	t_vec3	*coord;
	t_vec3	*tmp;
	t_vec3	*arb;
	t_mat44	*mat;

	fwd = vec3_unit(cam->norm, 0);
	coord = cam->xyz;
	tmp = vec3_init(0, 1, 0);
	arb = vec3_unit(tmp, 1);
	mat = camera_lookat_utils(fwd, coord, arb);
	free(fwd);
	free(arb);
	return (mat);
}

/* src: https://math.stackexchange.com/questions/89621/how-to-multiply-vector-3-with-4by4-matrix-more-precisely-position-transformat */

t_vec3	*vec3_matrix_multiply(t_mat44 *mat, t_vec3 *vec, double w)
{
	t_vec3	*res;
	double	a;
	double	b;
	double	c;

	a = (mat->a[0] * vec->e[0]) + (mat->b[0] * vec->e[1]) \
						+ (mat->c[0] * vec->e[2]) + (mat->d[0] * w);
	b = (mat->a[1] * vec->e[0]) + (mat->b[1] * vec->e[1]) \
						+ (mat->c[1] * vec->e[2]) + (mat->d[1] * w);
	c = (mat->a[2] * vec->e[0]) + (mat->b[2] * vec->e[1]) \
						+ (mat->c[2] * vec->e[2]) + (mat->d[2] * w);
	res = vec3_init(a, b, c);
	return (res);
}
