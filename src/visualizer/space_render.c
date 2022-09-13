/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/13 02:25:00 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	*set_direction(t_param param, t_mat44 *mat)
{
	double	x;
	double	y;
	t_vec3	*tmp;
	t_vec3	*unit;
	t_vec3	*direction;

	x = (2 * (param.px + 0.5) / param.width - 1) * \
								param.scale * param.aspect_ratio;
	y = (1 - 2 * (param.py + 0.5) / param.height) * param.scale;
	tmp = vec3_init(x, y, 1);
	if (!tmp)
		return (NULL);
	unit = vec3_unit(tmp, 1);
	if (!unit)
		return (NULL);
	direction = vec3_matrix_multiply(mat, unit, 0);
	free(unit);
	return (direction);
}

int	space_set_lights(t_space *space, t_obj_lst *elem)
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
		return (1);
	i = 0;
	elem = space->objects;
	while (elem)
	{
		if (elem->type == LIGHT)
			space->lights[i++] = (t_light *)elem->content;
		elem = elem->next;
	}
	space->lights[i] = NULL;
	return (0);
}

int	init_parameters(int width, int height, t_space *space, t_param *param)
{
	int	y;
	int	x;

	param->width = width;
	param->height = height;
	if (space_set_lights(space, space->objects))
		return (1);
	param->matrix = camera_lookat(space->camera);
	if (!param->matrix)
		return (1);
	param->scale = tan(deg2rad(space->camera->fov / 2));
	param->aspect_ratio = (double)param->width / (double)param->height;
	param->colour = 0;
	y = -1;
	while (++y < param->height)
	{
		x = -1;
		while (++x < param->width)
		{
			param->screen_hit[y][x] = '?';
			param->screen_shading[y][x] = '?';
		}
	}
	return (0);
}

void	print_screens_and_free_matrix(t_param *param)
{
	print_screen(param->screen_hit);
	print_screen(param->screen_shading);
	free(param->matrix);
}

void	space_render(t_data *data, int width, int height, t_space *space)
{
	t_param	param;
	t_ray	ray;

	if (init_parameters(width, height, space, &param))
		return ;
	ray.origin = space->camera->xyz;
	adjust_plane_norm(space->objects, ray.origin);
	param.py = -1;
	while (++param.py < param.height)
	{
		param.px = -1;
		while (++param.px < param.width)
		{
			ray.direction = set_direction(param, param.matrix);
			if (ray.direction)
			{
				param.colour = cast_ray(&ray, space, \
					&param.screen_hit[(int)param.py][(int)param.px], \
					&param.screen_shading[(int)param.py][(int)param.px]);
				free(ray.direction);
			}
			my_mlx_pixel_put(data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	print_screens_and_free_matrix(&param);
}