/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/18 22:23:56 by omoudni          ###   ########.fr       */
=======
/*   Updated: 2022/09/18 20:40:16 by swillis          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	surface_rgb_normal(t_hit *hit, t_object *obj, t_ray *r, t_shade *shade)
{
	double	u;
	double	v;

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
			vec_copy(obj->pl.rgb, &shade->rgb);
			vec_copy(obj->pl.norm, &shade->normal);

		//	double	t = ray->origin->e[2] / ray->direction->e[2];
		//		printf("%f %f\n", vec3_len(obj->pl.e1), vec3_len(obj->pl.e2));
			//	u = vec3_dot(vec3_unit(vec3_subtract(hit->phit, obj->pl.xyz), 1), obj->pl.e1) * 0.5 + 0.5;
				//v = vec3_dot(vec3_unit(vec3_subtract(hit->phit, obj->pl.xyz), 1), obj->pl.e2) * 0.5 + 0.5;
				u = fabs(fmod(vec3_dot(vec3_divide(vec3_subtract(hit->phit, obj->pl.xyz), 100), obj->pl.e1), 1));
				v = (fmod(vec3_dot(vec3_divide(vec3_subtract(hit->phit, obj->pl.xyz), 100), obj->pl.e2), 1));
				// u = vec3_dot(vec3_divide(vec3_subtract(hit->phit, obj->pl.xyz), 100), obj->pl.e1) * 0.5 + 0.5;
				// v = vec3_dot(vec3_divide(vec3_subtract(hit->phit, obj->pl.xyz), 100), obj->pl.e2) * 0.5 + 0.5;
//			printf("e1.x: %f e1.y: %f, e1.z: %f\n", obj->pl.e1->e[0], obj->pl.e1->e[1], obj->pl.e1->e[2]);
		//	printf("e2.x: %f e2.y: %f, e2.z: %f\n", obj->pl.e2->e[0], obj->pl.e2->e[1], obj->pl.e2->e[2]);
//			u = ray->origin->e[0] + ray->direction->e[0] * t;
		//	v = ray->origin->e[1] + ray->direction->e[1] * t;
			printf("u: %f, v: %f\n", u, v);
			if (v < 0)
			{
				if ((((int)(fabs(u) * 1000)) /100 + ((int)(v * 1000)) / 100) % 2)
					shade->rgb = vec3_init(255, 0, 0);
				else
					shade->rgb = vec3_init(255, 255, 255);
			}
			else
			{
				if ((((int)(fabs(u) * 1000)) /100 + ((int)(v * 1000)) / 100) % 2)
					shade->rgb = vec3_init(255, 255, 255);
				else
					shade->rgb = vec3_init(255, 0, 0);
			}
//			shade->rgb = obj->pl.rgb;
			shade->normal = vec3_copy(obj->pl.norm);
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
			if (shade->specular_comp / shade->ks > 0.01)
				hit->shading = '*';
		}
		else if (shade->diffuse_comp / shade->kd > 0.5)
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
	vec_multiply(shade.diffuse, shade.kd, &shade.diffuse);
	vec_multiply(shade.specular, shade.ks, &shade.specular);
	vec_add(hit->rgb, shade.ambient, &hit->rgb);
	vec_add(hit->rgb, shade.diffuse, &hit->rgb);
	vec_add(hit->rgb, shade.specular, &hit->rgb);
	rgb_multiply(hit->rgb, shade.rgb, &hit->rgb);
}
