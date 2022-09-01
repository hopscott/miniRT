/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/02 01:06:05 by swillis          ###   ########.fr       */
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

t_vec3	*secondary_ray_origin(t_ray *ray, double t)
{
	t_vec3	*dist;
	t_vec3	*phit;

	dist = vec3_multiply(ray->direction, t);
	phit = vec3_add(ray->origin, dist);
	free(dist);
	return (phit);
}

// PHONG REFLECTION
// We use the Phong illumation model int the default case. The phong model is composed of a diffuse and a specular reflection component. 
//                 Vec3f lightAmt = 0, specularColor = 0; 
//                 Vec3f shadowPointOrig = (dotProduct(dir, N) < 0) ? 
//                     hitPoint + N * options.bias : 
//                     hitPoint - N * options.bias; 
// Loop over all lights in the scene and sum their contribution up We also apply the lambert cosine law here though we haven't explained yet what this means. 
//                 for (uint32_t i = 0; i < lights.size(); ++i) { 
//                     Vec3f lightDir = lights[i]->position - hitPoint; 
//                     // square of the distance between hitPoint and the light
//                     float lightDistance2 = dotProduct(lightDir, lightDir); 
//                     lightDir = normalize(lightDir); 
//                     float LdotN = std::max(0.f, dotProduct(lightDir, N)); 
//                     Object *shadowHitObject = nullptr; 
//                     float tNearShadow = kInfinity; 
//                     // is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
//                     bool inShadow = trace(shadowPointOrig, lightDir, objects, tNearShadow, index, uv, &shadowHitObject) && 
//                         tNearShadow * tNearShadow < lightDistance2; 
//                     lightAmt += (1 - inShadow) * lights[i]->intensity * LdotN; 
//                     Vec3f reflectionDirection = reflect(-lightDir, N); 
//                     specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, dir)), hitObject->specularExponent) * lights[i]->intensity; 
//                 } 
//                 hitColor = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks; 
//                 break; 

size_t	cast_ray(t_ray *ray, t_space *space)
{
	t_object	*obj;
	t_vec3		*normal;
	t_hit		hit;
	t_ray		secray;
	t_hit		sechit;
	t_light		*light;
	size_t		colour;

	hit.nearest = NULL;
	hit.secondary = &secray;
	nearest_hit_object(ray, space->objects, &hit);
	if (hit.nearest)
	{
		sechit.nearest = NULL;
		hit.secondary->origin = secondary_ray_origin(ray, hit.t);
		obj = (t_object *)(hit.nearest->content);
		if (hit.nearest->type == LIGHT)
		{
			hit.rgb = vec3_multiply(vec3_init(obj->l.r, obj->l.g, obj->l.b), obj->l.brightness_ratio);
		}
		if (hit.nearest->type == SPHERE)
		{
			hit.rgb = rgb_multiply(vec3_init(obj->sp.r, obj->sp.g, obj->sp.b), vec3_multiply(vec3_init(space->ambient->r, space->ambient->g, space->ambient->b), space->ambient->lighting_ratio));
		}
		else if (hit.nearest->type == PLANE)
		{
			normal = vec3_init(obj->pl.vec_x, obj->pl.vec_y, obj->pl.vec_z);
			hit.secondary->direction = plane_secondary_ray_direction(ray->direction, normal);
			nearest_hit_object(hit.secondary, space->objects, &sechit);
			if (sechit.nearest == NULL)
			{
				hit.rgb = rgb_multiply(vec3_init(obj->pl.r, obj->pl.g, obj->pl.b), vec3_multiply(vec3_init(space->ambient->r, space->ambient->g, space->ambient->b), space->ambient->lighting_ratio));
			}
			else if (sechit.nearest->type == LIGHT)
			{
				light = (t_light *)(sechit.nearest->content);
				hit.rgb = rgb_multiply(vec3_init(obj->pl.r, obj->pl.g, obj->pl.b), vec3_multiply(vec3_init(light->r, light->g, light->b), light->brightness_ratio));
			}
			else
			{
				hit.rgb = vec3_init(0, 0, 0);
			}
			free(hit.secondary->direction);
		}
		else if (hit.nearest->type == CYLINDER)
			;
		free(hit.secondary->origin);
	}
	else
	{
		hit.rgb = vec3_multiply(vec3_init(space->ambient->r, space->ambient->g, space->ambient->b), space->ambient->lighting_ratio);
	}
	colour = rgb_colour(hit.rgb);
	free(hit.rgb);
	return (colour);
}
