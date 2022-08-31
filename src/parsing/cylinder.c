/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/08/30 17:52:17 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*build_cylinder(char **tbl)
{
	t_cylinder		*obj;
	char			**xyz;
	char			**rgb;

	obj = malloc(sizeof(t_cylinder));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	obj->x = (double)ft_atod(xyz[0]);
	obj->y = (double)ft_atod(xyz[1]);
	obj->z = (double)ft_atod(xyz[2]);
	ft_freetbl(xyz, -1);
	xyz = ft_split(tbl[2], ',');
	obj->vec_x = (double)ft_atod(xyz[0]);
	obj->vec_y = (double)ft_atod(xyz[1]);
	obj->vec_z = (double)ft_atod(xyz[2]);
	ft_freetbl(xyz, -1);
	obj->diameter = (double)ft_atod(tbl[3]);
	obj->height = (double)ft_atod(tbl[4]);
	rgb = ft_split(tbl[5], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	return (obj);
}
