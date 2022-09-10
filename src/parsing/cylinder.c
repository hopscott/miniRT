/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/11 01:17:14 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_cylinder_vecs(t_cylinder **obj)
{
	(*obj)->xyz = vec3_init((*obj)->x, (*obj)->y, (*obj)->z);
	(*obj)->norm = vec3_unit(vec3_init((*obj)->vec_x, (*obj)->vec_y, (*obj)->vec_z), 1);
	(*obj)->rgb = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
}

t_cylinder	*build_cylinder(char **tbl, int to_switch)
{
	t_cylinder		*obj;
	char			**tmp;

	obj = malloc(sizeof(t_cylinder));
	if (!obj)
		return (NULL);
	tmp = ft_split(tbl[1], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (NULL);
	obj->x = (double)ft_atod(tmp[0]);
	if (to_switch)
	{
		obj->x = to_switch * (double)ft_atod(tmp[0]);
		obj->y = to_switch * (double)ft_atod(tmp[2]);
		obj->z = (double)ft_atod(tmp[1]);
	}
	else
	{
		obj->y = (double)ft_atod(tmp[1]);
		obj->z = (double)ft_atod(tmp[2]);
	}
	ft_freetbl(tmp, -1);
	tmp = ft_split(tbl[2], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (NULL);
	obj->vec_x = (double)ft_atod(tmp[0]);
	if (to_switch)
	{
		obj->vec_x = to_switch * (double)ft_atod(tmp[0]);
		obj->vec_y = to_switch * (double)ft_atod(tmp[2]);
		obj->vec_z = (double)ft_atod(tmp[1]);
	}
	else
	{
		obj->vec_y = (double)ft_atod(tmp[1]);
		obj->vec_z = (double)ft_atod(tmp[2]);
	}
	ft_freetbl(tmp, -1);
	obj->diameter = (double)ft_atod(tbl[3]);
	obj->height = (double)ft_atod(tbl[4]);
	tmp = ft_split(tbl[5], ',');
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (NULL);
	obj->r = (size_t)ft_atoi(tmp[0]);
	obj->g = (size_t)ft_atoi(tmp[1]);
	obj->b = (size_t)ft_atoi(tmp[2]);
	ft_freetbl(tmp, -1);
	build_cylinder_vecs(&obj);
	return (obj);
}
