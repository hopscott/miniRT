/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/06 23:52:06 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_checkerboard_rgb(t_hit *hit, double surf_rgb[3], \
									int type, double (*rgb)[3])
{
	int		u2;
	int		v2;
	double	ncheckers_size;
	double	max[3];

	ncheckers_size = 1;
	if (type == SPHERE)
		ncheckers_size = 40;
	else if (type == PLANE)
		ncheckers_size = 10;
	else if (type == CYLINDER)
		ncheckers_size = 100;
	u2 = floor(hit->u * ncheckers_size);
	v2 = floor(hit->v * ncheckers_size);
	if ((u2 + v2) % 2 == 0)
		vec_copy(surf_rgb, rgb);
	else
	{
		vec_set(255, 255, 255, &max);
		vec_subtract(max, surf_rgb, rgb);
	}
}

void	set_texture_rgb(t_hit *hit, t_data *tex, double (*rgb)[3])
{
	int		x;
	int		y;
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
	x = (int)(hit->u * tex->w * tex->bpp / 8);
	x -= x % 4;
	y = (int)(hit->v * tex->h * tex->bpp / 8);
	y -= y % 4;
	color = tex->addr + x + (tex->w * y);
	rgb_pix[0] = fmod((double)color[2] / 255, 1) * 255;
	rgb_pix[1] = fmod((double)color[1] / 255, 1) * 255;
	rgb_pix[2] = fmod((double)color[0] / 255, 1) * 255;
	vec_copy(rgb_pix, rgb);
}
