/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/18 21:39:56 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================================	*/
/* calculate lambertian reflectance - diffuse 					*/
/* => https://en.wikipedia.org/wiki/Lambertian_reflectance		*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/ 	*/
/* introduction-to-shading/diffuse-lambertian-shading			*/
/* ============================================================	*/

void	add_diffuse_component(t_shade *shade, t_ray *lray, t_light *light)
{
	double	ratio;
	double	l[3];
	double	diffuse[3];

	vec_multiply(lray->direction, -1, &l);
	shade->diffuse_comp = shade->kd * vec_dot(l, shade->normal);
	if (shade->diffuse_comp > 0)
	{
		ratio = light->brightness_ratio;
		vec_multiply(light->rgb, ratio * shade->diffuse_comp, &diffuse);
		vec_add(shade->diffuse, diffuse, &shade->diffuse);
	}
}

/* ============================================================	*/
/* calculate specular reflectance 								*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/	*/
/* phong-shader-BRDF/phong-illumination-models-brdf				*/
/* ============================================================	*/

void	add_specular_component(t_shade *shade, t_ray *lray, t_light *light)
{
	double	ratio;
	double	v[3];
	double	r[3];
	double	specular[3];
	int		n;

	n = 20;
	vec_multiply(shade->normal, 2 * \
							vec_dot(shade->normal, lray->direction), &r);
	vec_subtract(r, lray->direction, &r);
	vec_copy(shade->ray->direction, &v);
	shade->specular_comp = shade->ks * pow(vec_dot(v, r), n);
	if (shade->specular_comp > 0)
	{
		ratio = light->brightness_ratio;
		vec_multiply(light->rgb, ratio * shade->specular_comp, &specular);
		vec_add(shade->specular, specular, &shade->specular);
	}
}

void	shading_from_light(t_space *space, t_hit *hit, \
									t_light *light, t_shade *shade)
{
	t_ray		lray;
	t_hit		lhit;

	vec_copy(light->xyz, &lray.origin);
	vec_subtract(hit->phit, light->xyz, &lray.direction);
	vec_unit(lray.direction, &lray.direction);
	nearest_hit_object(&lray, space->objects, &lhit);
	if (lhit.nearest)
	{
		shade->lobj = (t_object *)(lhit.nearest->content);
		if (shade->lobj == shade->obj)
		{
			add_diffuse_component(shade, &lray, light);
			add_specular_component(shade, &lray, light);
		}
	}
}
