/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:57:44 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/05 16:17:15 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat44	*set_ry(double	angle)
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

t_mat44	*set_rz(double	angle)
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

int	trans_to_cy(double (*trans_phit)[3], t_cylinder *cy, t_hit *hit)
{
	double	phi;
	double	theta;
	t_mat44	*rot_mat;

	if (cy->norm[0] == 0 && cy->norm[2] == 0 && cy->norm[1] == 1)
		return (1);
	if (cy->norm[2] == 0 || cy->norm[0] == 0)
		phi = 0;
	else
	{
		phi = atan(cy->norm[0] / cy->norm[2]);
		if (phi < 0)
			phi = 2 * M_PI + phi;
	}
	if (cy->norm[1] == 0)
		theta = 0;
	else
	{
		theta = atan(sqrt(pow(cy->norm[2], 2) + pow(cy->norm[0], 2)) / cy->norm[1]);
		if (theta < 0)
			theta = theta + M_PI;
	}
//	printf("phi: %f, theta: %f\n", phi, theta);
	rot_mat = set_rot_mat(phi, theta);
//	check_tr(cy, rot_mat);
	vec_matrix_multiply(rot_mat, hit->phit, 1, trans_phit);
	return (0);
}
//function to check if the transformation was succesful
/*
int	check_tr(t_cylinder *cy, t_mat44 *tr_mat)
{
	double	extr_pt[3];
	double	res[3];

	vec_matrix_multiply(tr_mat, cy->norm, 0, &res);
	printf("cy->norm : %f %f %f\n", cy->norm[0], cy->norm[1], cy->norm[2]);
	printf("cy->norm transformed:\n");
	printf("x_t: %f, y_t: %f, z_t: %f\n", res[0] , res[1], res[2]);
	vec_ray_distance_to_point(cy->xyz, res, cy->height, &extr_pt);
	printf("The top of the cylinder transformed:\n");
	printf("x_t: %f, y_t: %f, z_t: %f\n", extr_pt[0], extr_pt[1], extr_pt[2]);
	return (0);
}
*/
