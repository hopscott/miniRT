/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 17:02:14 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
