/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/08/31 01:24:20 by swillis          ###   ########.fr       */
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
		if ((hit->t >= 0) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
	return (hit);
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

size_t	cast_ray(t_ray *ray, t_space *space)
{
	t_object	*obj;
	t_vec3		*vec;
	t_hit		hit;
	t_ray		sec;
	size_t		colour;

	hit.nearest = NULL;
	hit.secondary = &sec;
	nearest_hit_object(ray, space->objects, &hit);
	if (hit.nearest)
	{
		hit.secondary->origin = secondary_ray_origin(ray, t);
		obj = (t_object *)(hit.nearest->content);
		if (hit.nearest->type == LIGHT)
		{
			vec = vec3_init(obj->l->r, obj->l->g, obj->l->b);
			hit.rgb = vec3_multiply(vec, obj->l->brightness_ratio);
			free(vec);
		}
		if (hit.nearest->type == SPHERE)
		{
			// printf("nearest obj = SPHERE => xyz(%.1f, %.1f, %.1f)\n", obj->sp.x, obj->sp.y, obj->sp.z);
			hit.rgb = vec3_init(obj->sp.r, obj->sp.g, obj->sp.b);
		}
		else if (hit.nearest->type == PLANE)
		{
			hit.secondary->direction = plane_secondary_ray_direction(ray, t);
			nearest_hit_object(hit.secondary, space->objects, &hit);
			// printf("nearest obj = PLANE => xyz(%.1f, %.1f, %.1f)\n", obj->pl.x, obj->pl.y, obj->pl.z);
			hit.rgb = vec3_init(obj->pl.r, obj->pl.g, obj->pl.b);
			free(hit.secondary->direction);
		}
		else if (hit.nearest->type == CYLINDER)
			;
		free(hit.secondary->origin);
	}
	else
	{
		vec = vec3_init(space->ambient->r, space->ambient->g, space->ambient->b);
		hit.rgb = vec3_multiply(vec, space->ambient->lighting_ratio);
		free(vec);
	}
	colour = rgb_colour(hit.rgb);
	free(hit.rgb);
	return (colour);
}
