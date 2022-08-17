/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/08/17 23:47:07 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */

// bool trace(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Object>> &objects, float &tNear, const Object *&hitObject) 
// { 
//     tNear = kInfinity; 
//     std::vector<std::unique_ptr<Object>>::const_iterator iter = objects.begin(); 
//     for (; iter != objects.end(); ++iter) { 
//         float t = kInfinity; 
//         if ((*iter)->intersect(orig, dir, t) && t < tNear) { 
//             hitObject = iter->get(); 
//             tNear = t; 
//         } 
//     } 
 
//     return (hitObject != nullptr); 
// } 

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

t_obj_list	*nearest_hit_object(t_vec3 *origin, t_vec3 *direction, t_obj_list **objects)
{
	double		tmin;
	t_obj_list	*nearest;
	t_obj_list	*elem;
	t_object	*obj;
	t_vec3		*vec;

	tmin = INFINITY;
	*nearest = NULL;
	elem = *objects;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == SPHERE)
		{
			vec = vec3_init(obj->sp->x, obj->sp->y, obj->sp->z);
			tmin = vec3_distance_points(origin, vec);
			free(vec);
			nearest = elem;
		}
		else if (elem->type == PLANE)
			continue ;
		else if (elem->type == CYLINDER)
			continue ;
		elem = elem->next;
	}
	return (nearest);
}

t_vec3	*cast_ray(t_vec3 *origin, t_vec3 *direction, t_space *space)
{
	t_obj_list		*olst;
	t_object		*obj;
	t_vec3			*rgb;
	// t_light			*light;

	// light = nearest_hit_light(origin, direction, space->lights);
	olst = nearest_hit_object(origin, direction, space->objects);
	if (olst)
	{		
		obj = (t_object *)(elem->content);
		if (elem->type == SPHERE)
			rgb = vec3_init(obj->sp->r, obj->sp->g, obj->sp->b);
		else if (elem->type == PLANE)
			continue ;
		else if (elem->type == CYLINDER)
			continue ;
	}
	else
		rgb = vec3_init(space->ambient->r * space->ambient->lighting_ratio, \
						space->ambient->g * space->ambient->lighting_ratio, \
						space->ambient->b * space->ambient->lighting_ratio);
	return (rgb);
}

void	render(int width, int height, t_space *space)
{
	int		px;
	int		py;
	double	x;
	double	y;
	t_mat44	*mat;
	t_vec3	*origin;
	t_vec3	*direction;
	t_vec3	*rgb;

	mat = camera_lookat(space->camera);
	origin = vec3_matrix_multiply(mat, vec3_init(0, 0, 0), 0);
	py = -1;
	while (++py < height)
	{
		px = -1;
		while (++px < width)
		{
			x = ((px + 0.5) / width) - 1;
			y = ((py + 0.5) / height) - 1;
			direction = vec3_matrix_multiply(mat, vec3_init(x, y, -1), 1);
			rgb = cast_ray(origin, direction, space);
			// colour_pixel(img->px, img->py, rgb);
		}
	}
	free(mat);
	free(origin);
	free(direction);
}
