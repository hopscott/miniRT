/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/08 20:39:29 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int		n;

	n = 20;
	tmp = vec3_multiply(shade->normal, 2 * \
							vec3_dot(shade->normal, lray->direction));
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
