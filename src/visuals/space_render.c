/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/01 22:55:02 by swillis          ###   ########.fr       */
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
	origin = vec3_matrix_multiply(mat, vec, 0);
	free(vec);
	return (origin);
}

void	space_render(t_data *data, int width, int height, t_space *space)
{
	t_param	param;
	t_mat44	*mat;
	t_ray	ray;

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
			param.colour = cast_ray(&ray, space);
			free(ray.direction);
			my_mlx_pixel_put(data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	free(mat);
	free(ray.origin);
}
