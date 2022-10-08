/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/17 17:54:27 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_light_vecs(t_light **obj)
{
	t_light	*l;

	l = *obj;
	vec_set(l->x, l->y, l->z, &l->xyz);
	vec_set(l->r, l->g, l->b, &l->rgb);
	vec_multiply(l->rgb, l->brightness_ratio, &l->rgb);
}

t_light	*sub_build_light(char **tbl, t_light **light)
{
	t_light	*obj;
	char	**rgb;

	obj = *light;
	obj->brightness_ratio = (double)ft_atod(tbl[2]);
	rgb = ft_split(tbl[3], ',');
	if (!rgb || tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
	{
		free(obj);
		return (tbl_free(&rgb), NULL);
	}
	rgb_helper(&(obj->r), &(obj->g), &(obj->b), rgb);
	ft_freetbl(rgb, -1);
	build_light_vecs(&obj);
	return (obj);
}

t_light	*build_light(char **tbl, int to_switch)
{
	t_light		*obj;
	char		**xyz;
	double		coord_switch[3];
	double		coord_not_switch[3];

	obj = malloc(sizeof(t_light));
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
	return (sub_build_light(tbl, &obj));
}
