/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 17:41:47 by swillis          ###   ########.fr       */
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

	x = (int)(hit->u * tex->w * tex->bpp / 8);
	y = (int)(hit->v * tex->h * tex->bpp / 8);
	color = tex->addr + x + tex->w * y;
	rgb_pix[0] = (double)color[2];
	rgb_pix[1] = (double)color[1];
	rgb_pix[2] = (double)color[2];
	vec_copy(rgb_pix, rgb);
}

void	set_rgb(t_hit *hit, double rgb[3], double size, t_shader *shader)
{
	if (hit->nearest->surface == NONE)
		vec_copy(rgb, &shader->rgb);
	else if (hit->nearest->surface == CHECKERS)
		set_checkerboard_rgb(hit, rgb, size, &shader->rgb);
	else if (hit->nearest->surface == TEXTURE)
		set_texture_rgb(hit, shader->texture, &shader->rgb);
}

void	surface_rgb_normal(t_hit *hit, t_object *obj, t_shader *shader)
{
	if ((hit->nearest) && (hit->nearest->type == SPHERE))
	{
		sphere_surface_normal(shader->ray, &obj->sp, hit->phit, \
														&shader->normal);
		set_uv_sphere(hit, &obj->sp);
		set_rgb(hit, obj->sp.rgb, 20, shader);
	}
	else if ((hit->nearest) && (hit->nearest->type == PLANE))
	{
		vec_copy(obj->pl.norm, &shader->normal);
		set_uv_plane(hit, &obj->pl);
		set_rgb(hit, obj->pl.rgb, 0.1, shader);
	}
	else if ((hit->nearest) && (hit->nearest->type == CYLINDER))
	{
		cylinder_surface_normal(&obj->cy, hit->phit, &shader->normal);
		set_uv_cylinder(hit, &obj->cy);
		set_rgb(hit, obj->cy.rgb, 5, shader);
	}
}
