/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_primitives.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:02:13 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/05 16:15:01 by omoudni          ###   ########.fr       */
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
	theta = acos(xyz[0] / r);
	phi = atan(xyz[2] / xyz[1]);
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
	hit->u = (1 - ((theta / (2 * M_PI)) + 0.5));
	hit->v = (1 - (phi / M_PI)) / 2;
	hit->u = fabs(hit->u);
	hit->v = fabs(hit->v);
	//	printf("u_sp: %f, v_sp: %f\n", hit->u, hit->v);
}

/* ======================================================== */
/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* ======================================================== */

void	set_uv_plane(t_hit *hit, t_plane *pl)
{
	hit->u = vec_dot(hit->phit, pl->e1);
	hit->v = vec_dot(hit->phit, pl->e2);
}

void	set_uv_cylinder(t_hit *hit, t_cylinder *cy)
{
	double	xyz[3];
	double	theta;
	double	raw_u;
	int		test;

	test = trans_to_cy(&xyz, cy, hit);
	if (test)
	{
		xyz[0] = hit->phit[0];
		xyz[1] = hit->phit[1];
		xyz[2] = hit->phit[2];
	}
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = (1 - (raw_u + 0.5));
	hit->v = ((xyz[1] - cy->xyz[1]) / cy->height) / 4;
}

void	set_texture(t_hit *hit, double (*rgb)[3], t_data *tex)
{
	int	x;
	int	y;
	char	*color;
	double	rgb_pix[3];

	if (hit->u < 0)
		hit->u = 0;
	if (hit->u > 1)
		hit->u = 1;
	if (hit->v < 0)
		hit->v = 0;
	if (hit->v > 1)
		hit->v = 1;
	x = (int)(hit->u * tex->w* tex->bpp/8);
	x -= x % 4;
	y = (int)(hit->v * tex->h * tex->bpp/8);
	y -= y % 4;
	color = tex->addr + x + tex->w * y;
	rgb_pix[0] = (double)color[2];
	rgb_pix[1] = (double)color[1];
	rgb_pix[2] = (double)color[0];
	vec_copy(rgb_pix, rgb);
}

void	set_checkerboard_rgb(t_hit *hit, double surf_rgb[3], double size, double (*rgb)[3])
{
	int		u;
	int		v;
	double	ncheckers_width;
	double	ncheckers_height;
	double	max[3];

	ncheckers_width = size;
	ncheckers_height = size;
	u = floor(hit->u * ncheckers_width);
	v = floor(hit->v * ncheckers_height);
	if ((u + v) % 2  == 0)
		vec_copy(surf_rgb, rgb);
	else
	{
		vec_set(255, 255, 255, &max);
		vec_subtract(max, surf_rgb, rgb);
	}
}
