/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 22:53:23 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*build_camera(char **tbl)
{
	t_camera	*obj;
	char		**xyz;
	char		**vec;

	obj = malloc(sizeof(t_camera));
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
	obj->fov = (size_t)ft_atoi(tbl[3]);
	return (obj);
}
