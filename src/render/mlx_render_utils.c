/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:55:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/08 18:04:18 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_img_addr_from_xpm(t_vars *vars, t_data *data, char *path)
{
	if (path)
	{
		if (access(path, F_OK) == 0)
		{
			data->img = mlx_xpm_file_to_image(vars->mlx, path, \
													&data->w, &data->h);
			if (!data->img)
			{
				data->img = NULL;
				data->addr = NULL;
			}
			else
				data->addr = mlx_get_data_addr(data->img, \
							&data->bpp, &data->line_length, &data->endian);
		}
	}
}

void	set_textures_and_bumps(t_vars *vars, char *texture, char *bump)
{
	int	i;

	i = -1;
	while (++i < MATERIALS)
	{
		vars->textures[i].img = NULL;
		vars->textures[i].addr = NULL;
		vars->bumps[i].img = NULL;
		vars->bumps[i].addr = NULL;
	}
	set_img_addr_from_xpm(vars, &vars->textures[WOOD], "assets/wood.xpm");
	set_img_addr_from_xpm(vars, &vars->textures[BRICK], "assets/brick.xpm");
	set_img_addr_from_xpm(vars, &vars->bumps[BRICK], "assets/brick_normal.xpm");
	set_img_addr_from_xpm(vars, &vars->textures[CUSTOM], texture);
	set_img_addr_from_xpm(vars, &vars->bumps[CUSTOM], bump);
}
