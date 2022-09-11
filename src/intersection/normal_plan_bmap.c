/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_plan_bmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:31:58 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/11 16:37:00 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	*normal_bmap_plane_mountains(t_plane *plane, t_hit *hit)
{
	t_vec3	*tmp;
	t_vec3	*normal;
	int		pixel;//bas: 0 haut: 1
	int		right;
	int		above;
	double	h;
	double	d_p;
	double	d_r;
	double	d_a;

	pixel = 1000;
	right = 1000;
	above = 1000;
	d_p = sqrt(pow(((int)(hit->phit->e[0] - plane->xyz->e[0]) % 10) - 4, 2) + pow(((int)(hit->phit->e[1] - plane->xyz->e[1]) % 10) - 4, 2));
	d_r = sqrt(pow(((int)(hit->phit->e[0] + 1 - plane->xyz->e[0]) % 10) - 4, 2) + pow(((int)(hit->phit->e[1] - plane->xyz->e[1]) % 10) - 4, 2));
	d_a = sqrt(pow(((int)(hit->phit->e[0] - plane->xyz->e[0]) % 10) - 4, 2) + pow(((int)(hit->phit->e[1] + 1 - plane->xyz->e[1]) % 10) - 4, 2));
	if ((int)((hit->phit->e[0] - plane->xyz->e[0]) / 10) % 2 && (int)((hit->phit->e[1] - plane->xyz->e[1]) / 10) % 2)
		pixel = 0 + d_p;
	if ((int)((hit->phit->e[0]+1 - plane->xyz->e[0]) / 10) % 2 && (int)((hit->phit->e[1] - plane->xyz->e[1]) / 10) % 2)
		right = 0 + d_r;
	if ((int)((hit->phit->e[0] - plane->xyz->e[0]) / 10) % 2 && (int)((hit->phit->e[1]+1 - plane->xyz->e[1]) / 10) % 2)
		above = 0 + d_a;
	tmp = vec3_init(plane->norm->e[0] + (pixel - right), plane->norm->e[1]  + (above - pixel), plane->norm->e[2]);

	h = sqrt(pow(pixel - above, 2) + pow(pixel - right, 2) + 1); 
	normal = vec3_unit(tmp, 1);
	   return (normal);
}

t_vec3	*normal_bmap_plane_lines(t_plane *plane, t_hit *hit)
{
	t_vec3	*tmp;
	t_vec3	*normal;

	if ((int)((hit->phit->e[0] - plane->xyz->e[0]) / 10) % 2)
	{
		tmp = vec3_init(plane->norm->e[0] - abs((int)hit->phit->e[0] % 10), plane->norm->e[1], plane->norm->e[2]);
		normal = vec3_unit(tmp, 1);
	}
	else
	{
		tmp = vec3_init(plane->norm->e[0] + abs((int)hit->phit->e[0] % 10), plane->norm->e[1], plane->norm->e[2]);
		normal = vec3_unit(tmp, 1);
	}
	return (normal);
}
