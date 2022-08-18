/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:55:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/18 19:01:04 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keypress(int key, t_vars *vars)
{
	(void)vars;
	printf("key = %d\n", key);
	if (key == 65307)
		mlx_loop_end(vars->mlx);
	return (0);
}

int	destroy(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

void	clear_window(t_vars *vars)
{
	ft_bzero(vars->data.addr, HEIGHT * WIDTH * 4);
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

int	render_frame(t_vars *vars)
{
	clear_window(vars);
	space_render(&vars->data, WIDTH, HEIGHT, vars->space);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (0);
}

void	mlx_render(t_space *space)
{
	t_vars	vars;

	vars.space = space;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.data.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &vars.data.bpp, &vars.data.line_length, &vars.data.endian);
	mlx_hook(vars.win, 2, 1L<<0, keypress, &vars);
	mlx_hook(vars.win, 17, 1L<<17, destroy, &vars);
	// mlx_loop_hook(vars.mlx, render_frame, &vars);
	space_render(&vars.data, WIDTH, HEIGHT, vars.space);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.data.img, 0, 0);
	mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, vars.data.img);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
