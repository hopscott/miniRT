/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 02:46:37 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*sub_build_sphere(t_sphere **sphere, char **tbl)
{
	char		**rgb;
	t_sphere	*obj;

	obj = *sphere;
	obj->diameter = (double)ft_atod(tbl[2]);
	rgb = ft_split(tbl[3], ',');
	if (!rgb || tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
	{
		free(obj);
		return (tbl_free(&rgb), NULL);
	}
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	obj->xyz = vec3_init(obj->x, obj->y, obj->z);
	if (!(obj->xyz))
		return (free(obj), NULL);
	obj->rgb = vec3_init(obj->r, obj->g, obj->b);
	if (!(obj->rgb))
	{
		free(obj->xyz);
		return (free(obj), NULL);
	}
	return (obj);
}

t_sphere	*build_sphere(char **tbl, int to_switch)
{
	t_sphere	*obj;
	char		**xyz;
	double		coord_switch[3];
	double		coord_not_switch[3];

	obj = malloc(sizeof(t_sphere));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	if (!xyz || tbl_3_check(xyz) || (!xyz[0] || !xyz[1] || !xyz[2]))
	{
		free(obj);
		return (tbl_free(&xyz), NULL);
	}
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, xyz);
	if (to_switch)
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_switch);
	else
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_not_switch);
	ft_freetbl(xyz, -1);
	return (sub_build_sphere(&obj, tbl));
}
