/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:12:26 by swillis           #+#    #+#             */
/*   Updated: 2022/09/01 22:47:54 by swillis          ###   ########.fr       */
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

t_vec3	*rgb_multiply(t_vec3 *rgb1, t_vec3 *rgb2)
{
	t_vec3	*rgb;
	size_t	r;
	size_t	g;
	size_t	b;

	r = (size_t)rgb1->e[0] * (size_t)rgb2->e[0] / 255;
	g = (size_t)rgb1->e[1] * (size_t)rgb2->e[1] / 255;
	b = (size_t)rgb1->e[2] * (size_t)rgb2->e[2] / 255;
	rgb = vec3_init(r, g, b);
	return (rgb);
}

// unsigned int	perc_colour(t_colour *c0, t_colour *c1, double p)
// {
// 	unsigned int	red;
// 	unsigned int	green;
// 	unsigned int	blue;

// 	red = c0->r * (1 - p) + c1->r * p;
// 	green = c0->g * (1 - p) + c1->g * p;
// 	blue = c0->b * (1 - p) + c1->b * p;
// 	return (rgb_colour(red, green, blue));
// }

// void	*routine(void *arg)
// {
// 	py = -1;
// 	while (++py < height)
// 	{
// 		px = -1;
// 		while (++px < width)
// 		{
// 			x = ((px + 0.5) / width);
// 			y = ((py + 0.5) / height);
// 			vec = vec3_init(x, y, -1);
// 			direction = vec3_matrix_multiply(mat, vec, 1);
// 			free(vec);
// 			rgb = cast_ray(origin, direction, space);
// 			free(direction);
// 			my_mlx_pixel_put(data, px, py, rgb_colour(rgb));
// 			printf("[%d][%d] => %X\n", px, py, rgb_colour(rgb));
// 			// vec3_print(rgb);
// 			free(rgb);
// 		}
// 	}
// }

// void	object_space_to_camera_space(t_list **lst)
// {
// 	t_list		*elem;
// 	t_object	*obj;

// 	elem = *lst;
// 	while (elem)
// 	{
// 		obj = (t_object *)(elem->content);
// 		if (elem->type == AMBIENT)
// 			continue ;
// 		else if (elem->type == CAMERA)
// 			continue ;
// 		else if (elem->type == LIGHT)
// 			continue ;
// 		else if (elem->type == SPHERE)
// 			continue ;
// 		else if (elem->type == PLANE)
// 			continue ;
// 		else if (elem->type == CYLINDER)
// 			continue ;
// 		elem = elem->next;
// 	}
// }
