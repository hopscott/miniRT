/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/06 23:54:52 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_light_components(t_space *space, t_shader *shader)
{
	t_ambient	*amb;

	amb = space->ambient;
	vec_multiply(amb->rgb, amb->lighting_ratio, &shader->ambient);
	shader->kd = 0.8;
	shader->diffuse_comp = 0;
	vec_set(0, 0, 0, &shader->diffuse);
	shader->ks = 0.15;
	shader->specular_comp = 0;
	vec_set(0, 0, 0, &shader->specular);
}

void	set_shading_char(t_shader *shader, t_hit *hit)
{
	if (shader->lobj == shader->obj)
	{
		if ((shader->specular_comp > shader->diffuse_comp))
		{
			if (shader->specular_comp > 0.001)
				hit->shading = '*';
		}
		else if (shader->diffuse_comp > 0.5)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

void	set_rgb_normal(t_hit *hit, double rgb[3], int type, t_shader *shader)
{
	vec_copy(rgb, &shader->rgb);
	if (hit->nearest->surface == CHECKERS)
		set_checkerboard_rgb(hit, rgb, type, &shader->rgb);
	else if (hit->nearest->surface == TEXTURE)
		set_texture_rgb(hit, shader->texture, &shader->rgb);
	else if (hit->nearest->surface == BUMP)
		set_bump_normal(hit, shader->bump, type, &shader->normal);
	else if (hit->nearest->surface == BUMPTEXT)
	{
		set_texture_rgb(hit, shader->texture, &shader->rgb);
		set_bump_normal(hit, shader->bump, type, &shader->normal);
	}
}

void	surface_rgb_normal(t_hit *hit, t_object *obj, t_shader *shader)
{
	if ((hit->nearest) && (hit->nearest->type == SPHERE))
	{
		sphere_surface_normal(shader->ray, &obj->sp, hit->phit, \
														&shader->normal);
		set_uv_sphere(hit, &obj->sp);
		vec_copy(obj->sp.rgb, &shader->rgb);
		set_rgb_normal(hit, obj->sp.rgb, SPHERE, shader);
	}
	else if ((hit->nearest) && (hit->nearest->type == PLANE))
	{
		vec_copy(obj->pl.norm, &shader->normal);
		set_uv_plane(hit, &obj->pl);
		vec_copy(obj->pl.rgb, &shader->rgb);
		set_rgb_normal(hit, obj->pl.rgb, PLANE, shader);
	}
	else if ((hit->nearest) && (hit->nearest->type == CYLINDER))
	{
		cylinder_surface_normal(&obj->cy, hit->phit, &shader->normal);
		set_uv_cylinder(hit, &obj->cy);
		vec_copy(obj->cy.rgb, &shader->rgb);
		set_rgb_normal(hit, obj->cy.rgb, CYLINDER, shader);
	}
}

/* ======================================================== */
/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/
/* ======================================================== */

void	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shader	shader;
	t_light		*light;
	size_t		i;

	shader.texture = hit->nearest->texture;
	shader.bump = hit->nearest->bump;
	shader.ray = ray;
	shader.obj = obj;
	surface_rgb_normal(hit, obj, &shader);
	init_light_components(space, &shader);
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		shading_from_light(space, hit, light, &shader);
		set_shading_char(&shader, hit);
	}
	vec_copy(shader.ambient, &hit->rgb);
	vec_add(hit->rgb, shader.diffuse, &hit->rgb);
	vec_add(hit->rgb, shader.specular, &hit->rgb);
	rgb_multiply(hit->rgb, shader.rgb, &hit->rgb);
}
