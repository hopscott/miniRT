/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping_cy_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 14:02:53 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat44	*set_ry(double angle)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*r_y;

	a[0] = cos(angle);
	a[1] = 0;
	a[2] = -sin(angle);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin(angle);
	c[1] = 0;
	c[2] = cos(angle);
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	r_y = mat44_init(a, b, c, d);
	return (r_y);
}

t_mat44	*set_rz(double angle)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*r_z;

	a[0] = cos(angle);
	a[1] = sin(angle);
	a[2] = 0;
	b[0] = -sin(angle);
	b[1] = cos(angle);
	b[2] = 0;
	c[0] = 0;
	c[1] = 0;
	c[2] = 1;
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	r_z = mat44_init(a, b, c, d);
	return (r_z);
}

t_mat44	*set_rot_mat(double phi, double theta)
{
	t_mat44	*r_y;
	t_mat44	*r_z;
	t_mat44	*r;

	r_y = set_ry(phi);
	if (!r_y)
		return (NULL);
	r_z = set_rz(theta);
	if (!r_z)
		return (free(r_y), NULL);
	r = mat_x_mat(r_z, r_y, 1);
	return (r);
}

double	get_phi(double cy_norm[3])
{
	double	phi;

	if (cy_norm[2] == 0)
		phi = 0;
	else if (cy_norm[0] == 0 && cy_norm[2] < 0)
		phi = M_PI / 2 + M_PI;
	else if (cy_norm[0] == 0 && cy_norm[2] > 0)
		phi = M_PI / 2;
	else
	{
		phi = atan(cy_norm[0] / cy_norm[2]);
		if (phi < 0)
			phi = phi + 2 * M_PI;
	}
	return (phi);
}

int	trans_to_cy(double (*trans_phit)[3], double cy_norm[3], t_hit *hit, int i)
{
	double	phi;
	double	theta;
	t_mat44	*rot_mat;

	phi = get_phi(cy_norm);
	if (cy_norm[1] == 0)
		theta = M_PI / 2;
	else
	{
		theta = atan(sqrt(pow(cy_norm[2], 2) + pow(cy_norm[0], 2))
				/ (cy_norm[1]));
		if (theta < 0)
			theta = theta + M_PI;
	}
	rot_mat = set_rot_mat(phi, theta);
	if (!rot_mat)
		return (1);
	if (i == 1)
		vec_matrix_multiply(rot_mat, hit->phit, 1, trans_phit);
	else
		vec_matrix_multiply_bis(rot_mat, hit->phit, 1, trans_phit);
	return (free(rot_mat), 0);
}
