/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 13:21:30 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fatal_error(t_space *space)
{
	space->fatal_error = 1;
}

void	free_params(t_param *param)
{
	free(param->matrix);
}

void	set_surfaces(t_data *textures, t_data *bumps, t_obj_lst **lst)
{
	t_obj_lst	*elem;
	t_data		*data;

	if (!lst)
		return ;
	elem = *lst;
	while (elem)
	{
		if ((elem->surface == TEXTURE) || (elem->surface == BUMPTEXT))
		{
			data = &textures[elem->material];
			elem->texture = data;
			if (!data->img || !data->addr)
				elem->surface = NONE;
		}
		else if ((elem->surface == BUMP) || (elem->surface == BUMPTEXT))
		{
			data = &bumps[elem->material];
			elem->bump = data;
			if (!data->img || !data->addr)
				elem->surface = NONE;
		}
		elem = elem->next;
	}
}

/* ====== */
/* DEBUG  */
/* ====== */
/*
void	free_params(t_param *param)
{
	tbl_free(&param->screen_shading);
	tbl_free(&param->screen_hit);
	free(param->matrix);
}

int	write_screen_to_file(char *path, int height, int width, char **screen)
{
	int	i;
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	i = -1;
	while (++i < height)
	{
		write(fd, screen[i], width);
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

void	print_screens_and_free_matrix(t_param *param)
{
	int	height;
	int	width;

	height = param->height;
	width = param->width;
	print_screen(param->screen_hit);
	print_screen(param->screen_shading);
	if (write_screen_to_file("hit.txt", height, width, param->screen_hit))
		return (free_params(param));
	if (write_screen_to_file("shading.txt", height, width, \
													param->screen_shading))
		return (free_params(param));
	free_params(param);
}
*/
