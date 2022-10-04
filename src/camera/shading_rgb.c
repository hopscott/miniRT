/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/21 03:53:36 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_checkerboard_rgb(t_hit *hit, double surf_rgb[3], \
									double size, double (*rgb)[3])
{
	int		u2;
	int		v2;
	double	ncheckers_width;
	double	ncheckers_height;
	double	max[3];

	ncheckers_width = size;
	ncheckers_height = size;
	u2 = floor(hit->u * ncheckers_width);
	v2 = floor(hit->v * ncheckers_height);
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

	if (hit->u > 1)
		hit->u = 1;
	if (hit->v > 1)
		hit->v = 1;
	x = (int)(hit->u * tex->w * tex->bpp / 8);
	x -= x % 4;
	y = (int)(hit->v * tex->h * tex->bpp / 8);
	y -= y % 4;

	// printf("u: %f | v: %f || x: %d | y: %d\n", hit->u, hit->v, x, y);

	color = tex->addr + x + (tex->w * y);
	rgb_pix[0] = (double)color[2];
	rgb_pix[1] = (double)color[1];
	rgb_pix[2] = (double)color[0];
	vec_copy(rgb_pix, rgb);
}