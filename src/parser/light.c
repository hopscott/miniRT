/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 22:30:58 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_light_vecs(t_light **obj)
{
	t_vec3	*tmp;

	(*obj)->xyz = vec3_init((*obj)->x, (*obj)->y, (*obj)->z);
	if (!((*obj)->xyz))
		return (1);
	tmp = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
	if (!tmp)
		return (free((*obj)->xyz), 1);
	(*obj)->rgb = vec3_multiply(tmp, (*obj)->brightness_ratio);
	free(tmp);
	if (!((*obj)->rgb))
		return (free((*obj)->xyz), 1);
	return (0);
}

t_light	*build_light(char **tbl, int to_switch)
{
	t_light		*obj;
	char		**xyz;
	char		**rgb;

	obj = malloc(sizeof(t_light));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	if (!xyz || tbl_3_check(xyz) || (!xyz[0] || !xyz[1] || !xyz[2]))
		return (tbl_free(&xyz), NULL);
	obj->x = (double)ft_atod(xyz[0]);
	if (to_switch)
	{
		obj->x = to_switch * (double)ft_atod(xyz[0]);
		obj->y = to_switch * (double)ft_atod(xyz[2]);
		obj->z = (double)ft_atod(xyz[1]);
	}
	else
	{
		obj->y = (double)ft_atod(xyz[1]);
		obj->z = (double)ft_atod(xyz[2]);
	}
	ft_freetbl(xyz, -1);
	obj->brightness_ratio = (double)ft_atod(tbl[2]);
	rgb = ft_split(tbl[3], ',');
	if (!rgb || tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
		return (tbl_free(&rgb), NULL);
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	if (build_light_vecs(&obj))
		return (free(obj), NULL);
	return (obj);
}
