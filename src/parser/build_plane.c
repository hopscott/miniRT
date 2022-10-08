/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 00:43:41 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_e1_e2(t_space *space, t_plane *plane)
{
	vec_cross(space->arb_vecs.v1, plane->norm, &plane->e1);
	if (fabs(vec_dot(space->arb_vecs.v1, plane->norm)) == 1)
	{
		vec_cross(space->arb_vecs.v2, plane->norm, &plane->e1);
		if (fabs(vec_dot(space->arb_vecs.v2, plane->norm)) == 1)
			vec_cross(space->arb_vecs.v3, plane->norm, &plane->e1);
	}
	vec_unit(plane->e1, &plane->e1);
	vec_cross(plane->norm, plane->e1, &plane->e2);
	vec_unit(plane->e2, &plane->e2);
}

void	build_plane_vecs(t_plane *obj)
{
	vec_set(obj->x, obj->y, obj->z, &obj->xyz);
	vec_set(obj->vec_x, obj->vec_y, obj->vec_z, &obj->norm);
	vec_unit(obj->norm, &obj->norm);
	vec_set(obj->r, obj->g, obj->b, &obj->rgb);
}

t_plane	*sub_build_plane(char **tbl, int to_switch, t_plane **obj)
{
	char		**vec;
	double		coord_switch[3];
	double		coord_not_switch[3];

	vec = ft_split(tbl[2], ',');
	if (!vec || tbl_3_check(vec) || (!vec[0] || !vec[1] || !vec[2]))
		return (pl_cy_tbl_free(NULL, obj, &vec), NULL);
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, vec);
	if (to_switch)
		build_helper_2(&(((*obj))->vec_x), &((*obj)->vec_y), \
									&((*obj)->vec_z), coord_switch);
	else
		build_helper_2(&((*obj)->vec_x), &((*obj)->vec_y), \
								&((*obj)->vec_z), coord_not_switch);
	ft_freetbl(vec, -1);
	if (!(*obj)->vec_x && !(*obj)->vec_y && !(*obj)->vec_z)
		return (free(*obj), NULL);
	vec = ft_split(tbl[3], ',');
	if (!vec || tbl_3_check(vec) || (!vec[0] || !vec[1] || !vec[2]))
		return (pl_cy_tbl_free(NULL, obj, &vec), NULL);
	rgb_helper(&((*obj)->r), &((*obj)->g), &((*obj)->b), vec);
	ft_freetbl(vec, -1);
	build_plane_vecs(*obj);
	return (*obj);
}

t_plane	*build_plane(t_space *space, char **tbl, int to_switch)
{
	t_plane		*obj;
	char		**xyz;
	double		coord_switch[3];
	double		coord_not_switch[3];

	obj = malloc(sizeof(t_plane));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	if (!xyz || tbl_3_check(xyz) || (!xyz[0] || !xyz[1] || !xyz[2]))
		return (pl_cy_tbl_free(NULL, &obj, &xyz), NULL);
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, xyz);
	if (to_switch)
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_switch);
	else
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_not_switch);
	ft_freetbl(xyz, -1);
	obj = sub_build_plane(tbl, to_switch, &obj);
	set_e1_e2(space, obj);
	return (obj);
}
