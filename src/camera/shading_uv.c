/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/04 23:04:55 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ======================================================== */
/* https://en.wikipedia.org/wiki/Spherical_coordinate_system */
/* ======================================================== */

void	set_uv_sphere(t_hit *hit, t_sphere *sp)
{
	double	xyz[3];
	double	r;
	double	theta;
	double	phi;

	vec_subtract(hit->phit, sp->xyz, &xyz);
	r = vec_len(xyz);
	theta = acos(xyz[1] / r);
	phi = atan(xyz[2] / xyz[0]);
	if (xyz[0] < 0)
	{
		if (xyz[1] >= 0)
			phi += M_PI;
		else
			phi -= M_PI;
	}
	if (xyz[0] == 0)
	{
		if (xyz[1] >= 0)
			phi = M_PI;
		else
			phi = -M_PI;
	}
	hit->u = 2 * (1 - ((theta / (2 * M_PI)) + 0.5));
	hit->v = 1 - (phi / M_PI);
}

/* ======================================================== */
/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* ======================================================== */

void	set_uv_plane(t_hit *hit, t_plane *pl)
{
	double	xyz[3];

	vec_subtract(hit->phit, pl->xyz, &xyz);
	vec_divide(xyz, 100, &xyz);
	hit->u = fabs(fmod(vec_dot(xyz, pl->e1), 1));
	hit->v = fabs(fmod(vec_dot(xyz, pl->e2), 1));
}

t_mat44	*mat44_init_cylinder(double angle_y, t_cylinder *cy)
{
	t_mat44	*ret;
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];

	a[0] = cos((angle_y / 180) * M_PI);
	a[1] = 0;
	a[2] = -sin((angle_y / 180) * M_PI);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin((angle_y / 180) * M_PI);
	c[1] = 0;
	c[2] = cos((angle_y / 180) * M_PI);
	d[0] = -cy->xyz[0];
	d[1] = -cy->xyz[1];
	d[2] = -cy->xyz[2];
	ret = mat44_init(a, b, c, d);
	return (ret);
}

void	trans_to_cy(double (*trans_phit)[3], t_cylinder *cy, t_hit *hit)
{
	t_mat44	*mat;
	double	angle_y;

	angle_y = acos(1 / cy->norm_magnitude);
	mat = mat44_init_cylinder(angle_y, cy);
	vec_matrix_multiply(mat, hit->phit, 1, trans_phit);
}

void	set_uv_cylinder(t_hit *hit, t_cylinder *cy)
{
	double	cy_center[3];
	double	xyz[3];
	double	theta;
	double	raw_u;
	double	tot_y_cy;

	vec_set(cy->xyz[0], cy->xyz[1], cy->xyz[2], &cy_center);
	trans_to_cy(&xyz, cy, hit);
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = 1 - (raw_u + 0.5);
	tot_y_cy = cy->xyz[1] + cy->height * cy->norm[1];
	hit->v = (hit->phit[1] - cy_center[1]) / tot_y_cy;
}