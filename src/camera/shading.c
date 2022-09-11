/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/11 16:44:32 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	surface_rgb_normal(t_hit *hit, t_object *obj, t_ray *ray, t_shade *shade)
{
	shade->ray = ray;
	shade->obj = obj;
	shade->rgb = NULL;
	shade->normal = NULL;
	if (hit->nearest)
	{
		if (hit->nearest->type == SPHERE)
		{
			shade->rgb = obj->sp.rgb;
			shade->normal = sphere_surface_normal(&obj->sp, hit->phit);
		}
		else if (hit->nearest->type == PLANE)
		{
			shade->rgb = obj->pl.rgb;
			shade->normal = vec3_copy(obj->pl.norm);
		}
		else if (hit->nearest->type == CYLINDER)
		{
			shade->rgb = obj->cy.rgb;
			shade->normal = cylinder_surface_normal(&obj->cy, hit->phit);
		}
		if (!shade->normal)
			return (1);
	}
	return (0);
}

int	init_light_components(t_space *space, t_shade *shade)
{
	t_ambient	*amb;

	shade->ambient = NULL;
	shade->diffuse = NULL;
	shade->specular = NULL;
	amb = space->ambient;
	shade->ambient = vec3_multiply(amb->rgb, amb->lighting_ratio);
	if (!shade->ambient)
		return (1);
	shade->kd = 0.8;
	shade->diffuse_comp = 0;
	shade->diffuse = vec3_init(0, 0, 0);
	if (!shade->diffuse)
		return (1);
	shade->ks = 0.15;
	shade->specular_comp = 0;
	shade->specular = vec3_init(0, 0, 0);
	if (!shade->specular)
		return (1);
	return (0);
}

void	set_shading_char(t_shade *shade, t_hit *hit)
{
	if (shade->lobj == shade->obj)
	{
		if ((shade->specular_comp > shade->diffuse_comp))
		{
			if (shade->specular_comp / shade->ks > 0.01)
				hit->shading = '*';
		}
		else if (shade->diffuse_comp / shade->kd > 0.5)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

int	shade_free(t_shade *shade, int err)
{
	if (shade->normal)
		free(shade->normal);
	if (shade->ambient)
		free(shade->ambient);
	if (shade->diffuse)
		free(shade->diffuse);
	if (shade->specular)
		free(shade->specular);
	return (err);
}

/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/
int	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shade		shade;
	t_light		*light;
	size_t		i;

	if (surface_rgb_normal(hit, obj, ray, &shade))
		return (1);
	if (init_light_components(space, &shade))
		return (shade_free(&shade, 1));
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		if (shading_from_light(space, hit, light, &shade))
			return (shade_free(&shade, 1));
		set_shading_char(&shade, hit);
	}
	vec3_multiply_to_self(&shade.diffuse, shade.kd);
	vec3_multiply_to_self(&shade.specular, shade.ks);
	vec3_add_to_self(&hit->rgb, shade.ambient);
	vec3_add_to_self(&hit->rgb, shade.diffuse);
	vec3_add_to_self(&hit->rgb, shade.specular);
	rgb_multiply_to_self(&hit->rgb, shade.rgb);
	return (shade_free(&shade, 0));
}
