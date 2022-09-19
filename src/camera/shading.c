/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 14:50:21 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ======================================================== */
/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* ======================================================== */

void	set_uv_plane(t_hit *hit, t_object *obj)
{
	hit->u = vec_dot(hit->phit, obj->pl.e1);
	hit->v = vec_dot(hit->phit, obj->pl.e2);
}

void	set_checkerboard_rgb(t_hit *hit, t_object *obj, double (*rgb)[3])
{
	int		u2;
	int		v2;
	double	ncheckers_width;
	double	ncheckers_height;
	double	max[3];

	ncheckers_width = 0.1;
	ncheckers_height = 0.1;
	u2 = floor(hit->u * ncheckers_width);
	v2 = floor(hit->v * ncheckers_height);
	if ((u2 + v2) % 2 == 0)
		vec_copy(obj->pl.rgb, rgb);
	else
	{
		vec_set(255, 255, 255, &max);
		vec_subtract(max, obj->pl.rgb, rgb);
	}
}

void	surface_rgb_normal(t_hit *hit, t_object *obj, t_ray *r, t_shade *shade)
{
	shade->ray = r;
	shade->obj = obj;
	if (hit->nearest)
	{
		if (hit->nearest->type == SPHERE)
		{
			vec_copy(obj->sp.rgb, &shade->rgb);
			sphere_surface_normal(r, &obj->sp, hit->phit, &shade->normal);
		}
		else if (hit->nearest->type == PLANE)
		{
			set_uv_plane(hit, obj);
			set_checkerboard_rgb(hit, obj, &shade->rgb);
			vec_copy(obj->pl.norm, &shade->normal);
		}
		else if (hit->nearest->type == CYLINDER)
		{
			vec_copy(obj->cy.rgb, &shade->rgb);
			cylinder_surface_normal(&obj->cy, hit->phit, &shade->normal);
		}
	}
}

void	init_light_components(t_space *space, t_shade *shade)
{
	t_ambient	*amb;

	amb = space->ambient;
	vec_multiply(amb->rgb, amb->lighting_ratio, &shade->ambient);
	shade->kd = 0.8;
	shade->diffuse_comp = 0;
	vec_set(0, 0, 0, &shade->diffuse);
	shade->ks = 0.15;
	shade->specular_comp = 0;
	vec_set(0, 0, 0, &shade->specular);
}

void	set_shading_char(t_shade *shade, t_hit *hit)
{
	if (shade->lobj == shade->obj)
	{
		if ((shade->specular_comp > shade->diffuse_comp))
		{
			if (shade->specular_comp > 0.01)
				hit->shading = '*';
		}
		else if (shade->diffuse_comp > 0.9)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/
void	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shade		shade;
	t_light		*light;
	size_t		i;

	surface_rgb_normal(hit, obj, ray, &shade);
	init_light_components(space, &shade);
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		shading_from_light(space, hit, light, &shade);
		set_shading_char(&shade, hit);
	}
	vec_copy(shade.ambient, &hit->rgb);
	vec_add(hit->rgb, shade.diffuse, &hit->rgb);
	vec_add(hit->rgb, shade.specular, &hit->rgb);
	rgb_multiply(hit->rgb, shade.rgb, &hit->rgb);
}
