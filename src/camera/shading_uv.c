/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_uv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/06 14:40:00 by omoudni          ###   ########.fr       */
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

void	set_uv_cylinder(t_hit *hit, t_cylinder *cy)
{
	double	xyz[3];
	double	theta;
	double	raw_u;
	int		test;
	double	new_norm[3];

	if (cy->norm[0] == 0 && cy->norm[2] == 0 && cy->norm[1] == 1)
	{
		xyz[0] = hit->phit[0];
		xyz[1] = hit->phit[1];
		xyz[2] = hit->phit[2];
	}
	else if (cy->norm[0] < 0)
	{
		get_new_norm(cy->norm, &new_norm);
		test = trans_to_cy(&xyz, new_norm, hit, 2);
	}
	else
		test = trans_to_cy(&xyz, cy->norm, hit, 1);
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = (1 - (raw_u + 0.5));
	hit->v = ((xyz[1] - cy->xyz[1]) / cy->height) / 4;
}
