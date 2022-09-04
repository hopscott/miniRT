/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/04 02:10:46 by omoudni          ###   ########.fr       */
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

int	plane_intersection(t_vec3 *origin, t_vec3 *direction, t_plane *plane)
{
	double	t;
	t_vec3	*p0;
	t_vec3	*n;
	t_vec3	*vec;

	p0 = vec3_init(plane->x, plane->y, plane->z);
	n = vec3_init(plane->vec_x, plane->vec_y, plane->vec_z);
	vec = vec3_subtract(p0, origin);
	t = vec3_dot(vec, n) / vec3_dot(direction, n);
	free(p0);
	free(n);
	free(vec);
	return (t);
}

void	nearest_ho_utils(t_obj_lst **nearest, t_obj_lst *elem, double *tmin, double t)
{
			if ((t >= 0) && (t < *tmin))
			{
				*nearest = elem;
				*tmin = t;
			}
}

t_obj_lst	*nearest_hit_object(t_vec3 *origin, t_vec3 *direction, t_obj_lst **objects)
{
	double		t;
	double		tmin;
	t_obj_lst	*nearest;
	t_obj_lst	*elem;
	t_object	*obj;
	//	t_vec3		*vec;

	tmin = INFINITY;
	nearest = NULL;
	elem = *objects;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == SPHERE)
		{
//			printf("\nor_x: %f, or_y: %f, or_z:%f\n", origin->e[0], origin->e[1], origin->e[2]);
//			printf("\nsp_x: %f, sp_y: %f, sp_z:%f\n",(obj->sp).x,(obj->sp).y, (obj->sp).z);
			t = sphere_intersection(origin, direction, &obj->sp);
			nearest_ho_utils(&nearest, elem, &tmin, t);
		}
		else if (elem->type == PLANE)
		{
			t = plane_intersection(origin, direction, &obj->pl);
			nearest_ho_utils(&nearest, elem, &tmin, t);
		}
		else if (elem->type == CYLINDER)
		{	
			//printf("\nor_x: %f, or_y: %f, or_z:%f\n", origin->e[0], origin->e[1], origin->e[2]);
//			printf("\ncyl_x: %f, cyl_y: %f, cyl_z:%f\n",(obj->cy).x,(obj->cy).y, (obj->cy).z);
			t = cy_intersection(origin, direction, &obj->cy);
			printf("t: %f\n", t);
//			if (t > -1)
//				printf("\nI found a cylinder. here is the t to it: %f\n", t);
			nearest_ho_utils(&nearest, elem, &tmin, t);
		}
			;
		elem = elem->next;
	}
	return (nearest);
}

t_vec3	*cast_ray(t_vec3 *origin, t_vec3 *direction, t_space *space)
{
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
			// printf("nearest obj = SPHERE => xyz(%.1f, %.1f, %.1f)\n", obj->sp.x, obj->sp.y, obj->sp.z);
			rgb = vec3_init(obj->sp.r, obj->sp.g, obj->sp.b);
		}
		else if (olst->type == PLANE)
		{
			// printf("nearest obj = PLANE => xyz(%.1f, %.1f, %.1f)\n", obj->pl.x, obj->pl.y, obj->pl.z);
			rgb = vec3_init(obj->pl.r, obj->pl.g, obj->pl.b);
		}
		else if (olst->type == CYLINDER)
		{
			rgb = vec3_init(obj->cy.r, obj->cy.g, obj->cy.b);
		}
	}
	if (!olst)
		rgb = vec3_init(space->ambient->r * space->ambient->lighting_ratio, \
				space->ambient->g * space->ambient->lighting_ratio, \
				space->ambient->b * space->ambient->lighting_ratio);
	return (rgb);
}

unsigned int	rgb_colour(t_vec3 *rgb)
{
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

double  deg2rad(double degree)
{
	return (degree * (M_PI / 180));
}

void	print_progress(int i, int total)
{
	char	*str1;
	char	*str2;

	if (total < 10)
		return ;

	if ((i > 1) && (i % (total / 10) == 0))
	{
		str1 = ft_strdup("##########");
		str2 = ft_strdup("          ");
		//printf("\e[?25l\r[%s%s]", &str1[10 - (i / (total / 10))], &str2[(i / (total / 10)) - 1]);
		printf("\r[%s%s]", &str1[10 - (i / (total / 10))], &str2[(i / (total / 10)) - 1]);
		fflush(stdout);
		free(str1);
		free(str2);
	}
}

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
	double	scale;
	double	aspect_ratio;

	printf("===== Running =====\n");
	scale = tan(deg2rad(space->camera->fov / 2));
	aspect_ratio = (double)width / (double)height;
	mat = camera_lookat(space->camera);
	vec = vec3_init(0, 0, 0);
	origin = vec3_matrix_multiply(mat, vec, 0);
	printf("origin.x: %f, origin.y: %f, origin.z: %f\n", origin->e[0], origin->e[1], origin->e[2]);
//	exit(0);
	//printf("\nor_x: %f, or_y: %f, or_z:%f\n", origin->e[0], origin->e[1], origin->e[2]);
	free(vec);
	py = -1;
	int	i;
	i = 0;
	while (++py < height)
	{
		px = -1;
		while (++px < width)
		{
			i++;
			x = (2 * (px + 0.5) / width - 1) * scale * aspect_ratio;
			y = (1 - 2 * (py + 0.5) / height) * scale;
			vec = vec3_init(x, y, -1);
			direction = vec3_matrix_multiply(mat, vec, 1);
			free(vec);
			rgb = cast_ray(origin, direction, space);
			free(direction);
			my_mlx_pixel_put(data, px, py, rgb_colour(rgb));
			print_progress(py, height);
			free(rgb);
		}
	}
	printf("\n------------------i: %d\n\n", i);
	free(mat);
	free(origin);
	printf("\n===== Finished =====\n");
}
