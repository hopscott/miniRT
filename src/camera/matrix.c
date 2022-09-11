/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/11 16:34:40 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/lessons/					 */
/* mathematics-physics-for-computer-graphics/lookat-function */

t_mat44	*mat44_init(t_vec3 *a, t_vec3 *b, t_vec3 *c, t_vec3 *d)
{
	t_mat44	*mat;
	int		i;

	if (!a | !b | !c | !d)
		return (NULL);
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

t_mat44	*camera_lookat_utils(t_vec3 *fwd, t_vec3 *old_coord, t_vec3 *right)
{
	t_vec3	*tmp;
	t_vec3	*up;
	t_vec3	*coord;
	t_mat44	*mat;

	tmp = vec3_cross(fwd, right);
	up = vec3_unit(tmp, 1);
	if (!up)
		return (NULL);
	coord = vec3_init(-vec3_dot(right, old_coord), \
						-vec3_dot(up, old_coord), -vec3_dot(fwd, old_coord));
	if (!coord)
	{
		free(up);
		return (NULL);
	}
	mat = mat44_init(right, up, fwd, coord);
	vec3_free_multi(up, coord, NULL, 0);
	return (mat);
}

t_mat44	*camera_lookat(t_camera *cam)
{
	t_vec3	*tmp;
	t_vec3	*fwd;
	t_vec3	*arb;
	t_vec3	*right;
	t_mat44	*mat;

	fwd = cam->norm;
	if (!fwd | !cam->xyz)
		return (NULL);
	tmp = vec3_init(0, 1, 0);
	arb = vec3_unit(tmp, 1);
	if (!arb)
		return (NULL);
	tmp = vec3_cross(arb, fwd);
	free(arb);
	right = vec3_unit(tmp, 1);
	if (!right)
		return (NULL);
	mat = camera_lookat_utils(fwd, cam->xyz, right);
	free(right);
	return (mat);
}

/* https://math.stackexchange.com/questions/89621/how-to-multiply-vector- */
/* 3-with-4by4-matrix-more-precisely-position-transformat 				  */

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
