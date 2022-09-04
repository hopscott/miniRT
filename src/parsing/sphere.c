/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/02 17:18:57 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*build_sphere(char **tbl)
{
	t_sphere	*obj;
	char		**xyz;
	char		**rgb;

	obj = malloc(sizeof(t_sphere));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	obj->x = (double)ft_atod(xyz[0]);
	obj->y = (double)ft_atod(xyz[1]);
	obj->z = (double)ft_atod(xyz[2]);
	ft_freetbl(xyz, -1);
	obj->diameter = (double)ft_atod(tbl[2]);
	rgb = ft_split(tbl[3], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	obj->xyz = vec3_init(obj->z, obj->y, obj->z);
	obj->rgb = vec3_init(obj->r, obj->g, obj->b);
	return (obj);
}
