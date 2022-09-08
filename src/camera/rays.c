/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/08 20:54:50 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/ */
/* 3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */

/*
	Vec3f castRay(
		const Vec3f &orig, const Vec3f &dir,
		const std::vector<std::unique_ptr<Object>> &objects)
	{
		Vec3f hitColor = 0;
		const Object *hitObject = nullptr;  //this is a pointer to the hit object
		float t;  //this is the intersection distance from the ray origin to the hit point
		if (trace(orig, dir, objects, t, hitObject)) {
			Vec3f Phit = orig + dir * t;
			Vec3f Nhit;
			Vec2f tex;
			hitObject->getSurfaceData(Phit, Nhit, tex);
			// Use the normal and texture coordinates to shade the hit point.
			// The normal is used to compute a simple facing ratio and the texture coordinate
			// to compute a basic checker board pattern
			float scale = 4;
			float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
			hitColor = std::max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
		}
		return hitColor;
	}
*/

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
			cy_intersection(ray, &obj->cy, hit);
		if ((hit->t >= 0.000001) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}

/* https://math.stackexchange.com/questions/13261/  */
/* how-to-get-a-reflection-vector 					*/
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

char	obj_to_char(t_obj_lst *elem)
{
	if (elem)
	{
		if (elem->type == LIGHT)
			return ('@');
		else if (elem->type == SPHERE)
			return ('o');
		else if (elem->type == PLANE)
			return ('-');
		else if (elem->type == CYLINDER)
			return ('%');
	}
	return ('.');
}

int	hit_init(t_ray *ray, t_space *space, t_hit *hit)
{
	hit->phit = NULL;
	hit->shading = '.';
	hit->rgb = vec3_init(0, 0, 0);
	if (!hit->rgb)
		return (1);
	nearest_hit_object(ray, space->objects, hit);
	return (0);
}

size_t	cast_ray(t_ray *ray, t_space *space, char *object, char *shading)
{
	t_hit		hit;
	t_object	*obj;
	size_t		colour;

	hit_init(ray, space, &hit);
	if (hit.nearest)
	{
		obj = (t_object *)(hit.nearest->content);
		hit.shading = '@';
		if (hit.nearest->type == LIGHT)
			vec3_add_to_self(&hit.rgb, obj->l.rgb);
		else
		{
			hit.phit = vec3_ray_distance_to_point(ray->origin, \
											ray->direction, hit.t);
			shading(space, ray, &hit, obj);
		}
	}
	else
		vec3_add_to_self(&hit.rgb, space->ambient->rgb);
	*object = obj_to_char(hit.nearest);
	*shading = hit.shading;
	colour = rgb_colour(hit.rgb);
	vec3_free_multi(hit.phit, hit.rgb, NULL, 0);
	return (colour);
}
