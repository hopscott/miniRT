/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 13:52:43 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_direction(t_param param, t_mat44 *mat, double (*res)[3])
{
	double	x;
	double	y;
	double	vec[3];

	x = (2 * (param.px + 0.5) / param.width - 1) * \
								param.scale * param.aspect_ratio;
	y = (1 - 2 * (param.py + 0.5) / param.height) * param.scale;
	vec_set(x, y, 1, &vec);
	vec_unit(vec, &vec);
	vec_matrix_multiply(mat, vec, 0, res);
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
	param->width = width;
	param->height = height;
	if (space_set_lights(space, space->objects))
		return (1);
	param->matrix = camera_lookat(space->camera);
	if (!param->matrix)
		return (1);
	param->scale = tan(((space->camera->fov / 2) * (M_PI / 180)));
	param->aspect_ratio = (double)param->width / (double)param->height;
	param->colour = 0;
	adjust_plane_norm(space->objects, space->camera->xyz);
	param->py = -1;
	return (0);
}

void	space_render(t_vars *vars, int width, int height, t_space *space)
{
	t_param	param;
	t_ray	ray;

	set_surfaces(vars->textures, vars->bumps, &space->objects);
	if (init_parameters(width, height, space, &param))
		return (fatal_error(space));
	vec_copy(space->camera->xyz, &ray.origin);
	adjust_plane_norm(space->objects, ray.origin);
	while (++param.py < param.height)
	{
		param.px = -1;
		while (++param.px < param.width)
		{
			set_direction(param, param.matrix, &ray.direction);
			param.colour = cast_ray(&ray, space, NULL, NULL);
			if (space->fatal_error)
				return (free_params(&param));
			my_mlx_pixel_put(&vars->data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	free_params(&param);
}

/* ====== */
/* DEBUG  */
/* ====== */
/*
int	sub_create_debugger(char ***tab, int dim_y, int dim_x)
{
	char	**tableau;
	int		i;
	int		j;

	tableau = *tab;
	tableau = (char **)malloc((dim_y + 1) * sizeof(char *));
	if (!tableau)
		return (1);
	i = -1;
	while (++i < dim_y)
	{
		tableau[i] = (char *)malloc((dim_x + 1) * sizeof(char));
		if (!tableau[i])
		{
			ft_freetbl(tableau, i - 1);
			return (1);
		}
		j = -1;
		while (++j < dim_x)
			tableau[i][j] = '?';
		tableau[i][j] = '\0';
	}
	tableau[i] = NULL;
	*tab = tableau;
	return (0);
}

int	init_parameters(int width, int height, t_space *space, t_param *param)
{
	param->width = width;
	param->height = height;
	if (space_set_lights(space, space->objects))
		return (1);
	param->matrix = camera_lookat(space->camera);
	if (!param->matrix)
		return (1);
	param->scale = tan(((space->camera->fov / 2) * (M_PI / 180)));
	param->aspect_ratio = (double)param->width / (double)param->height;
	param->colour = 0;
	if (sub_create_debugger(&param->screen_hit, height, width))
		return (1);
	if (sub_create_debugger(&param->screen_shading, height, width))
		return (1);
	adjust_plane_norm(space->objects, space->camera->xyz);
	param->py = -1;
	return (0);
}

void	space_render(t_vars *vars, int width, int height, t_space *space)
{
	t_param	param;
	t_ray	ray;

	set_surfaces(vars->textures, vars->bumps, &space->objects);
	if (init_parameters(width, height, space, &param))
		return (fatal_error(space));
	vec_copy(space->camera->xyz, &ray.origin);
	adjust_plane_norm(space->objects, ray.origin);
	while (++param.py < param.height)
	{
		param.px = -1;
		while (++param.px < param.width)
		{
			set_direction(param, param.matrix, &ray.direction);
			param.colour = cast_ray(&ray, space, \
						&param.screen_hit[(int)param.py][(int)param.px], \
						&param.screen_shading[(int)param.py][(int)param.px]);
			if (space->fatal_error)
				return (free_params(&param));
			my_mlx_pixel_put(&vars->data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	print_screens_and_free_matrix(&param);
}
*/
