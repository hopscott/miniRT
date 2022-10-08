/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:55:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/08 16:31:34 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keypress(int key, t_vars *vars)
{
	(void)vars;
	if (key == 65307)
		mlx_loop_end(vars->mlx);
	return (0);
}

int	destroy(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int px, int py, int color)
{
	char	*dst;

	if (((0 <= px) && (px < WIDTH)) && ((0 <= py) && (py < HEIGHT)))
	{
		dst = data->addr + (py * data->line_length + px * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	free_vars(t_vars *vars, t_space *space, int fatal)
{
	int	i;

	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	i = -1;
	while (++i < MATERIALS)
	{
		if (vars->textures[i].img || vars->textures[i].addr)
			mlx_destroy_image(vars->mlx, vars->textures[i].img);
		if (vars->bumps[i].img || vars->bumps[i].addr)
			mlx_destroy_image(vars->mlx, vars->bumps[i].img);
	}
	if (vars->data.img)
		mlx_destroy_image(vars->mlx, vars->data.img);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (fatal)
		fatal_error(space);
}

void	mlx_render(t_space *space, char *path_texture, char *path_bump)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (free_vars(&vars, space, 1));
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars.win)
		return (free_vars(&vars, space, 1));
	mlx_hook(vars.win, 2, 1L << 0, keypress, &vars);
	mlx_hook(vars.win, 17, 1L << 17, destroy, &vars);
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.data.img)
		return (free_vars(&vars, space, 1));
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bpp, \
							&vars.data.line_length, &vars.data.endian);
	set_textures_and_bumps(&vars, path_texture, path_bump);
	space_render(&vars, WIDTH, HEIGHT, space);
	if (!space->fatal_error)
		mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	if (!space->fatal_error)
		mlx_loop(vars.mlx);
	free_vars(&vars, space, 0);
}
