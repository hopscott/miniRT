/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/02 22:29:09 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */

// Vec3f castRay( 
//     const Vec3f &orig, const Vec3f &dir, 
//     const std::vector<std::unique_ptr<Object>> &objects) 
// { 
//     Vec3f hitColor = 0; 
//     const Object *hitObject = nullptr;  //this is a pointer to the hit object 
//     float t;  //this is the intersection distance from the ray origin to the hit point 
//     if (trace(orig, dir, objects, t, hitObject)) { 
//         Vec3f Phit = orig + dir * t; 
//         Vec3f Nhit; 
//         Vec2f tex; 
//         hitObject->getSurfaceData(Phit, Nhit, tex); 
//         // Use the normal and texture coordinates to shade the hit point.
//         // The normal is used to compute a simple facing ratio and the texture coordinate
//         // to compute a basic checker board pattern
//         float scale = 4; 
//         float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5); 
//         hitColor = std::max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern); 
//     } 
//     return hitColor; 
// } 

void	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit)
{
	double		tmin;
	t_object	*obj;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == LIGHT)
			light_intersection(ray, &obj->l, hit);
		else if (elem->type == SPHERE)
			sphere_intersection(ray, &obj->sp, hit);
		else if (elem->type == PLANE)
			plane_intersection(ray, &obj->pl, hit);
		else if (elem->type == CYLINDER)
			;
		if ((hit->t >= 0.000001) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}

t_vec3	*ray_to_point(t_ray *ray, double t)
{
	t_vec3	*dist;
	t_vec3	*xyz;

	dist = vec3_multiply(ray->direction, t);
	xyz = vec3_add(ray->origin, dist);
	free(dist);
	return (xyz);
}

// PHONG REFLECTION
// We use the Phong illumation model int the default case. 
// The phong model is composed of a diffuse and a specular reflection component. 
//                 Vec3f lightAmt = 0, specularColor = 0; 
//                 Vec3f shadowPointOrig = (dotProduct(dir, N) < 0) ? 
//                     hitPoint + N * options.bias : 
//                     hitPoint - N * options.bias; 
// Loop over all lights in the scene and sum their contribution up 
// We also apply the lambert cosine law here though we haven't explained yet what this means. 
//                 for (uint32_t i = 0; i < lights.size(); ++i) { 
//                     Vec3f lightDir = lights[i]->position - hitPoint; 
//                     // square of the distance between hitPoint and the light
//                     float lightDistance2 = dotProduct(lightDir, lightDir); 
//                     lightDir = normalize(lightDir); 
//                     float LdotN = std::max(0.f, dotProduct(lightDir, N)); 
//                     Object *shadowHitObject = nullptr; 
//                     float tNearShadow = kInfinity; 
//                     // is the point in shadow, 
//					   // and is the nearest occluding object closer to the object than the light itself?
//                     bool inShadow = trace(shadowPointOrig, lightDir, objects, tNearShadow, index, uv, &shadowHitObject) && 
//                         tNearShadow * tNearShadow < lightDistance2; 
//                     lightAmt += (1 - inShadow) * lights[i]->intensity * LdotN; 
//                     Vec3f reflectionDirection = reflect(-lightDir, N); 
//                     specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, dir)), hitObject->specularExponent) * lights[i]->intensity; 
//                 } 
//                 hitColor = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks; 
//                 break; 

/* https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector */

t_vec3	*reflection_vector(t_vec3 *direction, t_vec3 *normal)
{
	double	dot;
	t_vec3	*vec;
	t_vec3	*reflection;

	dot = vec3_dot(direction, normal);
	vec = vec3_multiply(normal, (2 * dot));
	reflection = vec3_subtract(direction, vec);
	free(vec);
	return (reflection);
}

void	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_vec3		*rgb;
	t_vec3		*normal;
	t_vec3		*tmp;
	t_vec3		*tmp2;
	t_vec3		*amb;
	t_vec3		*spec;
	t_vec3		*reflection_dir;
	t_ray		lray;
	t_hit		lhit;
	t_object	*lobj;
	t_light		*light;
	int			i;

	rgb = NULL;
	normal = NULL;
	if (hit->nearest->type == SPHERE)
	{
		rgb = obj->sp.rgb;
		normal = sphere_surface_normal(obj->sp, hit->phit);
	}
	else if (hit->nearest->type == PLANE)
	{
		rgb = obj->pl.rgb;
		normal = obj->pl.norm;
	}
	else if (hit->nearest->type == CYLINDER)
		;
	amb = vec3_init(0, 0, 0);
	i = -1;
	while (++i < space->n_lights)
	{
		light = space->lights[i];
		lray->origin = light->xyz;
		tmp = vec3_subtract(hit->phit, light->xyz);
		lray->direction = vec3_unit(tmp);
		free(tmp);
		nearest_hit_object(&lray, space->objects, &lhit);
		lobj = (t_object *)(lhit.nearest->content);
		if (lobj == obj)
		{
			tmp = vec3_multiply(light->rgb, vec3_dot(lray->direction, normal));
			tmp2 = vec3_add(amb, tmp);
			vec3_free_multi(tmp, amb);
			amb = tmp2;
		}
		reflection_dir = reflection_vector(lray->direction, normal);
		hit.rgb
	}
}

		// hit->secondary->direction = secondary_ray_direction(ray->direction, obj->pl.norm);
		// nearest_hit_object(hit->secondary, space->objects, &sechit);
		// if (sechit.nearest == NULL)
		// 	hit->rgb = rgb_multiply(obj->pl.rgb, space->ambient->rgb);
		// else if (sechit.nearest->type == LIGHT)
		// {
		// 	light = (t_light *)(sechit.nearest->content);
		// 	tmp = rgb_multiply(obj->pl.rgb, light->rgb);
		// 	hit->rgb = rgb_multiply(tmp, space->ambient->rgb);
		// }
		// free(hit->secondary->direction);

size_t	cast_ray(t_ray *ray, t_space *space)
{
	t_hit		hit;
	t_object	*obj;
	size_t		colour;

	nearest_hit_object(ray, space->objects, &hit);
	if (hit.nearest)
	{
		obj = (t_object *)(hit.nearest->content);
		if (hit.nearest->type == LIGHT)
			hit.rgb = vec3_copy(obj->l.rgb);
		else
		{
			hit.phit = ray_to_point(ray, hit.t);
			shading(space, ray, &hit, obj);
			free(hit.phit);
		}
	}
	else
		hit.rgb = vec3_copy(space->ambient->rgb);
	colour = rgb_colour(hit.rgb);
	free(hit.rgb);
	return (colour);
}
