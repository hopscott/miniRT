/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/08/18 18:57:46 by swillis          ###   ########.fr       */
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

int	intersects_sphere(t_vec3 *origin, t_vec3 *direction, t_sphere *sphere) {
	(void)origin;
	(void)direction;
	(void)sphere;
	return (1);
}

t_obj_lst	*nearest_hit_object(t_vec3 *origin, t_vec3 *direction, t_obj_lst **objects) {
	double		t;
	double		tmin;
	t_obj_lst	*nearest;
	t_obj_lst	*elem;
	t_object	*obj;
	t_vec3		*vec;

	(void)direction;
	tmin = INFINITY;
	nearest = NULL;
	elem = *objects;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if ((elem->type == SPHERE) && (intersects_sphere(origin, direction, &obj->sp)))
		{
			vec = vec3_init(obj->sp.x, obj->sp.y, obj->sp.z);
			t = vec3_distance_points(origin, vec);
			free(vec);
			if (t < tmin)
			{
				nearest = elem;
				tmin = t;
			}
		}
		else if (elem->type == PLANE)
			;
		else if (elem->type == CYLINDER)
			;
		elem = elem->next;
	}
	return (nearest);
}

t_vec3	*cast_ray(t_vec3 *origin, t_vec3 *direction, t_space *space) {
	t_obj_lst		*olst;
	t_object		*obj;
	t_vec3			*rgb;
	// t_light			*light;

	// light = nearest_hit_light(origin, direction, space->lights);
	olst = nearest_hit_object(origin, direction, &space->objects);
	if (olst)
	{
		obj = (t_object *)(olst->content);
		if (olst->type == SPHERE)
		{
			printf("nearest obj SPHERE -> xyz(%.1f, %.1f, %.1f)\n", obj->sp.x, obj->sp.y, obj->sp.z);
			rgb = vec3_init(obj->sp.r, obj->sp.g, obj->sp.b);
		}
		else if (olst->type == PLANE)
			;
		else if (olst->type == CYLINDER)
			;
	}
	if (!olst)
		rgb = vec3_init(space->ambient->r * space->ambient->lighting_ratio, \
						space->ambient->g * space->ambient->lighting_ratio, \
						space->ambient->b * space->ambient->lighting_ratio);
	return (rgb);
}

unsigned int	rgb_colour(t_vec3 *rgb) {
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)rgb->e[0];
	if (r > 255)
		r = 255;
	g = (unsigned int)rgb->e[1];
	if (g > 255)
		g = 255;
	b = (unsigned int)rgb->e[2];
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

// unsigned int	perc_colour(t_colour *c0, t_colour *c1, double p)
// {
// 	unsigned int	red;
// 	unsigned int	green;
// 	unsigned int	blue;

// 	red = c0->r * (1 - p) + c1->r * p;
// 	green = c0->g * (1 - p) + c1->g * p;
// 	blue = c0->b * (1 - p) + c1->b * p;
// 	return (rgb_colour(red, green, blue));
// }

// void	*routine(void *arg)
// {
// 	py = -1;
// 	while (++py < height)
// 	{
// 		px = -1;
// 		while (++px < width)
// 		{
// 			x = ((px + 0.5) / width);
// 			y = ((py + 0.5) / height);
// 			vec = vec3_init(x, y, -1);
// 			direction = vec3_matrix_multiply(mat, vec, 1);
// 			free(vec);
// 			rgb = cast_ray(origin, direction, space);
// 			free(direction);
// 			my_mlx_pixel_put(data, px, py, rgb_colour(rgb));
// 			printf("[%d][%d] => %X\n", px, py, rgb_colour(rgb));
// 			// vec3_print(rgb);
// 			free(rgb);
// 		}
// 	}
// }

// void	space_render_threading()

void	space_render(t_data *data, int width, int height, t_space *space)
{
	int		px;
	int		py;
	double	x;
	double	y;
	t_mat44	*mat;
	t_vec3	*origin;
	t_vec3	*direction;
	t_vec3	*vec;
	t_vec3	*rgb;

	printf("===== Running =====\n");
	mat = camera_lookat(space->camera);
	vec = vec3_init(0, 0, 0);
	origin = vec3_matrix_multiply(mat, vec, 0);
	free(vec);
	py = -1;
	while (++py < height)
	{
		px = -1;
		while (++px < width)
		{
			x = ((px + 0.5) / width);
			y = ((py + 0.5) / height);
			vec = vec3_init(x, y, -1);
			direction = vec3_matrix_multiply(mat, vec, 1);
			free(vec);
			rgb = cast_ray(origin, direction, space);
			free(direction);
			my_mlx_pixel_put(data, px, py, rgb_colour(rgb));
			printf("[%d][%d] => %X\n", px, py, rgb_colour(rgb));
			// vec3_print(rgb);
			free(rgb);
		}
	}
	free(mat);
	free(origin);
	printf("===== Finished =====\n");
}
