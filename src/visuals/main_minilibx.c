/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:55:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/15 15:10:57 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data
{
	void *img;
	char *addr;
	int bpp;
	int size_line;
	int endian;
	int width;
	int height;
}	t_data;
typedef struct s_vars
{
	void *mlx;
	void *win;
	t_data image;
}	t_vars;

int keypress(int key, t_vars *vars)
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
	bzero(vars->image.addr, HEIGHT * WIDTH * 4);
}

int	render_frame(t_vars *vars)
{
	clear_window(vars);
	//draw_background(&vars->image);
	draw_sprite(&vars->image, &vars->tex, vars->pos.x, vars->pos.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.pos.x = 0;
	vars.pos.y = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");
	vars.image.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.image.addr = mlx_get_data_addr(vars.image.img, &vars.image.bpp, &vars.image.size_line, &vars.image.endian);
	mlx_hook(vars.win, 2, 1L<<0, keypress, &vars);
	mlx_hook(vars.win, 17, 1L<<17, destroy, &vars);
	mlx_loop_hook(vars.mlx, render_frame, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_image(vars.mlx, vars.image.img);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (0);
}
