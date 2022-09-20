/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 15:10:07 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	surface_rgb_normal(t_hit *hit, t_object *obj, t_shade *shade)
{
	if ((hit->nearest) && (hit->nearest->type == SPHERE))
	{
		vec_copy(obj->sp.rgb, &shade->rgb);
		sphere_surface_normal(shade->ray, &obj->sp, hit->phit, &shade->normal);
		set_uv_sphere(hit, &obj->sp);
		if (hit->nearest->checkered)
			set_checkerboard_rgb(hit, obj->sp.rgb, 20, &shade->rgb);
	}
	else if ((hit->nearest) && (hit->nearest->type == PLANE))
	{
		vec_copy(obj->pl.rgb, &shade->rgb);
		vec_copy(obj->pl.norm, &shade->normal);
		set_uv_plane(hit, &obj->pl);
		if (hit->nearest->checkered)
			set_checkerboard_rgb(hit, obj->pl.rgb, 0.1, &shade->rgb);
	}
	else if ((hit->nearest) && (hit->nearest->type == CYLINDER))
	{
		vec_copy(obj->cy.rgb, &shade->rgb);
		cylinder_surface_normal(&obj->cy, hit->phit, &shade->normal);
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
		else if (shade->diffuse_comp > 0.5)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

/* ======================================================== */
/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/
/* ======================================================== */

void	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shade		shade;
	t_light		*light;
	size_t		i;

	shade.ray = ray;
	shade.obj = obj;
	surface_rgb_normal(hit, obj, &shade);
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
