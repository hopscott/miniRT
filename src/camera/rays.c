/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/08/17 16:29:23 by swillis          ###   ########.fr       */
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

t_list	*nearest_hit_object(t_vec3 *origin, t_vec3 *direction, t_list **objects)
{
	double		t;
	double		tmin;
	t_list		*elem;
	t_object	*obj;

	// iterate over each object to see if vec of len t intersects
	t = INFINITY;
	tmin = t;
	elem = *lst;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (((elem->type == LIGHT) && light_intersects(origin, direction, t)) && (t < tmin))
			tmin = t;
		else if (elem->type == SPHERE)
			continue ;
		else if (elem->type == PLANE)
			continue ;
		else if (elem->type == CYLINDER)
			continue ;
		elem = elem->next;
	}
	return (elem);
}

t_vec3	*cast_ray(t_vec3 *origin, t_vec3 *direction, t_list **objects)
{
	t_vec3		*rgb;
	t_list		*elem;
	t_object	*obj;

	elem = nearest_hit_object(origin, direction, objects);
	if (elem)
	{		
		obj = (t_object *)(elem->content);
		
		// hits light directly
		if (elem->type == LIGHT)
			rgb = vec3_init(obj->l.r * brightness_ratio, obj->l.g * brightness_ratio, obj->l.b * brightness_ratio);
		
		// hits other objects so shadow
		else if (elem->type == SPHERE)
			continue ;
		else if (elem->type == PLANE)
			continue ;
		else if (elem->type == CYLINDER)
			continue ;
	}
	
	// if no object hit = ambient lighting (-> need to set in a global data struct not linked list)
	else
		rgb = vec3_init(obj->a.r * lighting_ratio, obj->a.g * lighting_ratio, obj->a.b * lighting_ratio);
	return (rgb);
}

void	render(int width, int height, t_camera *camera, t_list **objects)
{
	int		px;
	int		py;
	double	x;
	double	y;
	t_mat44	*mat;
	t_vec3	*origin;
	t_vec3	*direction;
	t_vec3	*rgb;

	// convert camera origin point from ccs to wcs
	mat = camera_lookat(camera);
	origin = vec3_matrix_multiply(mat, vec3_init(0, 0, 0), 0);
	// convert each point on camera canvas in ccs to wcs
	py = -1;
	while (++py < height)
	{
		px = -1;
		while (++px < width)
		{
			// + 0.5 to aim at middle of pixel -> -1 to prevent overflow of mlx image
			x = ((px + 0.5) / width) - 1;
			y = ((py + 0.5) / height) - 1;
			direction = vec3_matrix_multiply(mat, vec3_init(x, y, -1), 1);
			rgb = cast_ray(origin, direction, objects);

			// colour_pixel(img->px, img->py, rgb);
		}
	}
	free(mat);
	free(origin);
	free(direction);
}
