/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:55:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/04 22:25:31 by swillis          ###   ########.fr       */
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

void	mlx_render(t_space *space, char *path_texture, char *path_bump)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (fatal_error(space));
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars.win)
		return (fatal_error(space));		// HERE
	mlx_hook(vars.win, 2, 1L << 0, keypress, &vars);
	mlx_hook(vars.win, 17, 1L << 17, destroy, &vars);
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	if (!vars.data.img)
		return (fatal_error(space));		// HERE
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bpp, \
							&vars.data.line_length, &vars.data.endian);
	set_textures_and_bumps(&vars, path_texture, path_bump);
	space_render(&vars, WIDTH, HEIGHT, space);
	if (!space->fatal_error)
		mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	if (!space->fatal_error)
		mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, vars.data.img);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
