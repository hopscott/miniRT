/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:12:26 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 14:44:39 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	deg2rad(double degree)
{
	return (degree * (M_PI / 180));
}

void	print_progress(int i, int total)
{
	char	*str1;
	char	*str2;

	if (i == 0)
		printf("\n====== Loading =======\n");
	if (i % (total / 20) == 0)
	{
		str1 = ft_strdup("####################");
		str2 = ft_strdup("                    ");
		printf("\r[%s%s]", &str1[19 - (i / (total / 20))], \
							&str2[(i / (total / 20)) + 1]);
		fflush(stdout);
		free(str1);
		free(str2);
	}
	else if (i == total - 1)
		printf("\n======================\n");
}

size_t	rgb_colour(t_vec3 *rgb)
{
	size_t	r;
	size_t	g;
	size_t	b;

	r = (size_t)rgb->e[0];
	if (r > 255)
		r = 255;
	g = (size_t)rgb->e[1];
	if (g > 255)
		g = 255;
	b = (size_t)rgb->e[2];
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

void	rgb_multiply_to_self(t_vec3 **rgb, t_vec3 *rgb2)
{
	t_vec3	*new;
	t_vec3	*rgb1;
	size_t	r;
	size_t	g;
	size_t	b;

	rgb1 = *rgb;
	r = (size_t)rgb1->e[0] * (size_t)rgb2->e[0] / 255;
	g = (size_t)rgb1->e[1] * (size_t)rgb2->e[1] / 255;
	b = (size_t)rgb1->e[2] * (size_t)rgb2->e[2] / 255;
	new = vec3_init(r, g, b);
	if (new)
	{
		free((*rgb));
		*rgb = new;
	}
}

void	print_screen(char screen[HEIGHT][WIDTH])
{
	int	y;	
	int	x;

	printf("    ");
	x = -1;
	while (++x < WIDTH + 2)
		if (x % 10 == 0)
			printf("_");
	printf("_\n");
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		if (y % 20 == 0)
			printf("%4d|", y);
		while (++x < WIDTH)
			if ((x % 10 == 0) && (y % 20 == 0))
				printf("%c", screen[y][x]);
		if (y % 20 == 0)
			printf("|\n");
	}
}
