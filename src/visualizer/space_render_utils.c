/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 16:51:15 by swillis          ###   ########.fr       */
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
	param->scale = tan(deg2rad(space->camera->fov / 2));
	param->aspect_ratio = (double)param->width / (double)param->height;
	param->colour = 0;
	if (sub_create_debugger(&param->screen_hit, height, width))
		return (1);
	if (sub_create_debugger(&param->screen_shading, height, width))
		return (1);
	adjust_plane_norm(space->objects, space->camera->xyz);
	return (0);
}

void	print_screens_and_free_matrix(t_param *param)
{
	print_screen(param->screen_hit);
	print_screen(param->screen_shading);
	tbl_free(&param->screen_shading);
	tbl_free(&param->screen_hit);
	free(param->matrix);
}
