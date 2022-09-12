/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 18:50:22 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_cylinder_vecs(t_cylinder **obj)
{
	t_vec3	*tmp;

	(*obj)->xyz = vec3_init((*obj)->x, (*obj)->y, (*obj)->z);
	if (!((*obj)->xyz))
		return (1);
	tmp = vec3_init((*obj)->vec_x, (*obj)->vec_y, (*obj)->vec_z);
	if (!tmp)
		return (free((*obj)->xyz), 1);
	(*obj)->norm = vec3_unit(tmp, 1);
	if (!((*obj)->norm))
		return (free((*obj)->xyz), 1);
	(*obj)->rgb = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
	if (!((*obj)->rgb))
	{
		free((*obj)->xyz);
		free((*obj)->norm);
		return (1);
	}
}

t_cylinder	*build_cylinder(char **tbl, int to_switch)
{
	t_cylinder		*obj;
	char			**tmp;

	obj = malloc(sizeof(t_cylinder));
	if (!obj)
		return (NULL);
	tmp = ft_split(tbl[1], ',');
	if (!tmp || tbl_3_check(tmp) || (!tmp[0] || !tmp[1] || !tmp[2]))
		return (tbl_free(&tmp), NULL);
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
	if (!tmp || tbl_3_check(tmp) || (!tmp[0] || !tmp[1] || !tmp[2]))
		return (tbl_free(&tmp), NULL);
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
	if (!tmp || tbl_3_check(tmp) || (!tmp[0] || !tmp[1] || !tmp[2]))
		return (tbl_free(&tmp), NULL);
	obj->r = (size_t)ft_atoi(tmp[0]);
	obj->g = (size_t)ft_atoi(tmp[1]);
	obj->b = (size_t)ft_atoi(tmp[2]);
	ft_freetbl(tmp, -1);
	if (build_cylinder_vecs(&obj))
		return (free(obj), NULL);
	return (obj);
}
