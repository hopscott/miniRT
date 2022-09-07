/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/07 19:44:05 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	surface_rgb_normal(t_hit *hit, t_object *obj, t_shade *shade)
{
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
			shade->normal = plane_surface_normal(&obj->pl, ray);
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

	amb = space->ambient;
	shade->ambient = vec3_multiply(amb->rgb, amb->lighting_ratio);
	if (!shade->ambient)
		return (1);
	shade->kd = 0.8;
	shade->diffuse = vec3_init(0, 0, 0);
	if (!shade->specular)
	{
		free(shade->ambient);
		return (1);
	}
	shade->ks = 0.15;
	shade->specular = vec3_init(0, 0, 0);
	if (!shade->specular)
	{
		vec3_free_multi(shade->ambient, shade->specular, NULL);
		return (1);
	}
	return (0);
}

/* calculate lambertian reflectance - diffuse 					*/
/* => https://en.wikipedia.org/wiki/Lambertian_reflectance		*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/ 	*/
/* introduction-to-shading/diffuse-lambertian-shading			*/
int	add_diffuse_component(t_shade *shade, t_ray *lray, t_light *light)
{
	t_vec3	*l;
	t_vec3	*tmp;

	l = vec3_multiply(lray->direction, -1);
	if (!l)
		return (1);
	free(l);
	shade->diffuse_comp = shade->kd * vec3_dot(l, shade->normal);
	if (shade->diffuse_comp > 0)
	{
		tmp = vec3_multiply(light->rgb, \
					light->brightness_ratio * shade->diffuse_comp);
		vec3_add_to_self(&diffuse, tmp);
		free(tmp);
	}
	return (0);
}

/* calculate specular reflectance 								*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/	*/
/* phong-shader-BRDF/phong-illumination-models-brdf				*/
int	add_specular_component(t_shade *shade, t_ray *lray, t_light *light)
{
	t_vec3	*v;
	t_vec3	*r;
	t_vec3	*tmp;
	double	ldotn;
	int		n;

	n = 20;
	ldotn = vec3_dot(shade->normal, lray->direction);
	tmp = vec3_multiply(shade->normal, 2 * ldotn);
	if (!tmp)
		return (1);
	r = vec3_subtract(tmp, lray.direction);
	free(tmp);
	if (!r)
		return (1);
	v = ray->direction;
	shade->specular_comp = shade->ks * pow(vec3_dot(v, r), n);
	if (shade->specular_comp > 0)
	{
		tmp = vec3_multiply(light->rgb, \
					light->brightness_ratio * shade->specular_comp);
		vec3_add_to_self(&specular, tmp);
		free(tmp);
	}
	return (0);
}

void	set_shading_char(t_char *shade, t_hit *hit)
{
	if (shade->lobj == obj)
	{
		if ((shade->specular_comp > shade->diffuse_comp))
		{
			if (shade->specular_comp > 0.001)
				hit->shading = '*';
		}
		else if (shade->diffuse_comp > 0.001)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

int	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shade		shade;
	t_ray		lray;
	t_hit		lhit;
	t_light		*light;
	size_t		i;

	if (surface_rgb_normal(hit, obj, &shade))
		return (1);
	if (init_light_components(space, &shade))
		return (1);
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		lray.origin = light->xyz;
		lray.direction = vec3_unit(vec3_subtract(hit->phit, light->xyz), 1);
		nearest_hit_object(&lray, space->objects, &lhit);
		if (lhit.nearest)
		{
			shade.lobj = (t_object *)(lhit.nearest->content);
			if (shade.lobj == obj)
			{
				add_diffuse_component(shade, lray, light);
				add_specular_component(shade, lray, light);
			}
		}
		free(lray.direction);
		set_shading_char(&shade, hit);
	}

	// https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF

	// diffuse * kd
	tmp = vec3_multiply(diffuse, kd);
	free(diffuse);
	diffuse = vec3_copy(tmp);
	free(tmp);

	// specular * ks
	tmp = vec3_multiply(specular, ks);
	free(specular);
	specular = vec3_copy(tmp);
	free(tmp);

	// ambient + diffuse + specular
	tmp = vec3_add(ambient, diffuse);
	hit->rgb = vec3_add(tmp, specular);
	tmp = rgb_multiply(rgb, hit->rgb);
	free(hit->rgb);
	hit->rgb = vec3_copy(tmp);
	vec3_free_multi(diffuse, specular, tmp);
	free(normal);
	return (c);
}
