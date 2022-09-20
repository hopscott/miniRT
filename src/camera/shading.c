/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 18:06:40 by swillis          ###   ########.fr       */
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
			if (shader->specular_comp > 0.01)
				hit->shading = '*';
		}
		else if (shader->diffuse_comp > 0.5)
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
	t_shader	shader;
	t_light		*light;
	size_t		i;

	shader.texture = space->texture;
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
