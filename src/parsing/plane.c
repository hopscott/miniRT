/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/06 14:00:42 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_plane_vecs(t_plane **obj)
{
	(*obj)->xyz = vec3_init((*obj)->x, (*obj)->y, (*obj)->z);
	(*obj)->norm = vec3_init((*obj)->vec_x, (*obj)->vec_y, (*obj)->vec_z);
	(*obj)->rgb = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
}

t_plane	*build_plane(char **tbl)
{
	t_plane		*obj;
	char		**xyz;
	char		**vec;
	char		**rgb;

	obj = malloc(sizeof(t_plane));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	obj->x = (double)ft_atod(xyz[0]);
	obj->y = (double)ft_atod(xyz[1]);
	obj->z = (double)ft_atod(xyz[2]);
	ft_freetbl(xyz, -1);
	vec = ft_split(tbl[2], ',');
	obj->vec_x = (double)ft_atod(vec[0]);
	obj->vec_y = (double)ft_atod(vec[1]);
	obj->vec_z = (double)ft_atod(vec[2]);
	ft_freetbl(vec, -1);
	rgb = ft_split(tbl[3], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	build_plane_vecs(&obj);
	return (obj);
}
