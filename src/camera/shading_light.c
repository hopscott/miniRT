/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/07 00:40:21 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================================	*/
/* calculate lambertian reflectance - diffuse 					*/
/* => https://en.wikipedia.org/wiki/Lambertian_reflectance		*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/ 	*/
/* introduction-to-shading/diffuse-lambertian-shading			*/
/* ============================================================	*/

void	add_diffuse_component(t_shader *shader, t_ray *lray, t_light *light)
{
	double	ratio;
	double	l[3];
	double	diffuse[3];

	vec_multiply(lray->direction, -1, &l);
	shader->diffuse_comp = shader->kd * vec_dot(l, shader->normal);
	if (shader->diffuse_comp > 0)
	{
		ratio = light->brightness_ratio;
		vec_multiply(light->rgb, ratio * shader->diffuse_comp, &diffuse);
		vec_add(shader->diffuse, diffuse, &shader->diffuse);
	}
}

/* ============================================================	*/
/* calculate specular reflectance 								*/
/* https://www.scratchapixel.com/lessons/3d-basic-rendering/	*/
/* phong-shader-BRDF/phong-illumination-models-brdf				*/
/* ============================================================	*/

void	add_specular_component(t_shader *shader, t_ray *lray, t_light *light)
{
	double	ratio;
	double	v[3];
	double	r[3];
	double	specular[3];
	int		n;

	n = 100;
	vec_multiply(shader->normal, 2 * \
							vec_dot(shader->normal, lray->direction), &r);
	vec_subtract(r, lray->direction, &r);
	vec_copy(shader->ray->direction, &v);
	shader->specular_comp = shader->ks * pow(vec_dot(v, r), n);
	if (shader->specular_comp > 0)
	{
		ratio = light->brightness_ratio;
		vec_multiply(light->rgb, ratio * shader->specular_comp, &specular);
		vec_add(shader->specular, specular, &shader->specular);
	}
}

void	shading_from_light(t_space *space, t_hit *hit, \
									t_light *light, t_shader *shader)
{
	t_ray		lray;
	t_hit		lhit;

	vec_copy(light->xyz, &lray.origin);
	vec_subtract(hit->phit, light->xyz, &lray.direction);
	vec_unit(lray.direction, &lray.direction);
	nearest_hit_object(&lray, space->objects, &lhit);
	if (lhit.nearest)
	{
		shader->lobj = (t_object *)(lhit.nearest->content);
		if (shader->lobj == shader->obj)
		{
			add_diffuse_component(shader, &lray, light);
			add_specular_component(shader, &lray, light);
		}
	}
}
