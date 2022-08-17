/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/17 21:06:30 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*build_light(char **tbl)
{
	t_light		*obj;
	char		**xyz;
	char		**rgb;

	obj = malloc(sizeof(t_light));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	obj->x = (double)ft_atod(xyz[0]);
	obj->y = (double)ft_atod(xyz[1]);
	obj->z = (double)ft_atod(xyz[2]);
	ft_freetbl(xyz, -1);
	obj->brightness_ratio = (double)ft_atod(tbl[2]);
	rgb = ft_split(tbl[3], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	return (obj);
}
