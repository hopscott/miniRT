/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/08 20:38:21 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	surface_rgb_normal(t_hit *hit, t_object *obj, t_shade *shade)
{
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

	shade->ambient = NULL;
	shade->diffuse = NULL;
	shade->specular = NULL;
	amb = space->ambient;
	shade->ambient = vec3_multiply(amb->rgb, amb->lighting_ratio);
	if (!shade->ambient)
		return (1);
	shade->kd = 0.8;
	shade->diffuse = vec3_init(0, 0, 0);
	if (!shade->specular)
		return (1);
	shade->ks = 0.15;
	shade->specular = vec3_init(0, 0, 0);
	if (!shade->specular)
		return (1);
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
	free(r);
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

int	shading_from_light(t_space *space, t_hit *hit, \
						t_light *light, t_shade *shade)
{
	t_ray		lray;
	t_hit		lhit;

	lray.origin = light->xyz;
	lray.direction = vec3_unit(vec3_subtract(hit->phit, light->xyz), 1);
	if (!lray.direction)
		return (1);
	nearest_hit_object(&lray, space->objects, &lhit);
	if (lhit.nearest)
	{
		shade.lobj = (t_object *)(lhit.nearest->content);
		if (shade.lobj == obj)
		{
			if (add_diffuse_component(shade, lray, light))
				return (1);
			if (add_specular_component(shade, lray, light))
				return (1);
		}
	}
	free(lray.direction);
}

/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/

int	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_shade		shade;
	t_light		*light;
	size_t		i;

	if (surface_rgb_normal(hit, obj, &shade))
		return (1);
	if (init_light_components(space, &shade))
		return (shade_free(shade, 1));
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		if (shading_from_light(space, hit, light, &shade))
			return (shade_free(shade, 1));
		set_shading_char(&shade, hit);
	}
	vec3_multiply_to_self(&diffuse, kd);
	vec3_multiply_to_self(&specular, ks);
	vec3_add_to_self(&hit->rgb, ambient);
	vec3_add_to_self(&hit->rgb, diffuse);
	vec3_add_to_self(&hit->rgb, specular);
	vec3_multiply_to_self(&hit->rgb, rgb);
	return (shade_free(shade, 0));
}
