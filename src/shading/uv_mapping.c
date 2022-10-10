/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 13:11:15 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* =========================================================== */
/* https://en.wikipedia.org/wiki/Spherical_coordinate_system   */
/* =========================================================== */
/* https://gamedev.stackexchange.com/questions/114412/         */
/* how-to-get-uv-coordinates-for-sphere-cylindrical-projection */
/* =========================================================== */

void	set_uv_sphere(t_hit *hit, t_sphere *sp)
{
	double	n[3];

	vec_subtract(hit->phit, sp->xyz, &n);
	vec_unit(n, &n);
	hit->theta = asin(n[1]);
	hit->phi = atan2(n[0], n[2]);
	hit->u = fabs((hit->phi / (2 * M_PI)) + 0.5);
	hit->v = fabs((hit->theta * 0.5 + 0.5) / 2);
}

/* ======================================================== */
/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* ======================================================== */

void	set_uv_plane(t_hit *hit, t_plane *pl)
{
	double	xyz[3];

	vec_subtract(hit->phit, pl->xyz, &xyz);
	vec_divide(xyz, 100, &xyz);
	hit->u = fmod(vec_dot(xyz, pl->e1), 1);
	if (hit->u < 0)
		hit->u = fmod(hit->u + 1, 1);
	hit->v = fmod(vec_dot(xyz, pl->e2), 1);
	if (hit->v < 0)
		hit->v = fmod(hit->v + 1, 1);
}

void	get_new_norm(double old_norm[3], double (*new_norm)[3])
{
	(*new_norm)[0] = -1 * old_norm[0];
	(*new_norm)[1] = old_norm[1];
	(*new_norm)[2] = -1 * old_norm[2];
}

void	set_uv_cylinder(t_space *space, t_hit *hit, t_cylinder *cy)
{
	double	xyz[3];
	double	theta;
	double	raw_u;
	double	new_norm[3];
	int		error;

	error = 0;
	if (cy->norm[0] == 0 && cy->norm[2] == 0 && cy->norm[1] == 1)
		vec_copy(hit->phit, &xyz);
	else if (cy->norm[0] < 0)
	{
		get_new_norm(cy->norm, &new_norm);
		error = trans_to_cy(&xyz, new_norm, hit, 2);
	}
	else
		error = trans_to_cy(&xyz, cy->norm, hit, 1);
	if (error)
	{
		space->fatal_error = 1;
		return ;
	}
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = (1 - (raw_u + 0.5));
	hit->v = ((xyz[1] - cy->xyz[1]) / cy->height) / 4;
}
