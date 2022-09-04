/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/05 00:50:26 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	*set_direction(t_param param, int width, int height, t_mat44 *mat)
{
	double	x;
	double	y;
	t_vec3	*vec;
	t_vec3	*direction;

	x = (2 * (param.px + 0.5) / width - 1) * param.scale * param.aspect_ratio;
	y = (1 - 2 * (param.py + 0.5) / height) * param.scale;
	vec = vec3_init(x, y, -1);
	direction = vec3_matrix_multiply(mat, vec, 1);
	free(vec);
	return (direction);
}

t_vec3	*set_origin(t_mat44 *mat)
{
	t_vec3	*vec;
	t_vec3	*origin;

	vec = vec3_init(0, 0, 0);
	origin = vec3_matrix_multiply(mat, vec, -1);
	free(vec);
	return (origin);
}

void	space_set_lights(t_space *space, t_obj_lst *elem)
{
	int	i;

	space->n_lights = 0;
	while (elem)
	{
		if (elem->type == LIGHT)
			space->n_lights++;
		elem = elem->next;
	}
	space->lights = malloc(sizeof(t_light *) * (space->n_lights + 1));
	if (!space->lights)
		return ;
	i = 0;
	elem = space->objects;
	while (elem)
	{
		if (elem->type == LIGHT)
			space->lights[i++] = (t_light *)elem->content;
		elem = elem->next;
	}
	space->lights[i] = NULL;
}

void	print_screen(char screen[HEIGHT][WIDTH])
{
	int	y;	
	int	x;

	printf("    ");
	x = -1;
	while (++x < WIDTH + 2)
		if (x % 10 == 0)
			printf("_");
	printf("_\n");
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		if (y % 20 == 0)
			printf("%4d|", y);
		while (++x < WIDTH)
			if ((x % 10 == 0) && (y % 20 == 0))
				printf("%c", screen[y][x]);
		if (y % 20 == 0)
			printf("|\n");
	}
	printf("    ");
	x = -1;
	while (++x < WIDTH + 2)
		if (x % 10 == 0)
			printf("_");
	printf("_\n");
}

void	space_render(t_data *data, int width, int height, t_space *space)
{
	t_param	param;
	t_mat44	*mat;
	t_ray	ray;
	char	screen[HEIGHT][WIDTH];

	space_set_lights(space, space->objects);
	mat = camera_lookat(space->camera);
	if (!mat)
		return ;
	param.scale = tan(deg2rad(space->camera->fov / 2));
	param.aspect_ratio = (double)width / (double)height;
	ray.origin = set_origin(mat);
	param.py = -1;
	while (++param.py < height)
	{
		param.px = -1;
		while (++param.px < width)
		{
			ray.direction = set_direction(param, width, height, mat);
			param.colour = cast_ray(&ray, space, &screen[(int)param.py][(int)param.px]);
			free(ray.direction);
			my_mlx_pixel_put(data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	print_screen(screen);
	free(mat);
	free(ray.origin);
}
