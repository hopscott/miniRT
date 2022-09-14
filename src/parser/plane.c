/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 02:48:23 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_plane_vecs(t_plane*obj)
{
	t_vec3	*tmp;
	obj->xyz = vec3_init(obj->x, obj->y, obj->z);
	if (!(obj->xyz))
		return (1);
	tmp = vec3_init(obj->vec_x, obj->vec_y, obj->vec_z);
	if (!tmp)
		return (free(obj->xyz), 1);
	obj->norm = vec3_unit(tmp, 1);
	if (!(obj->norm))
		return (free(obj->xyz), 1);
	obj->rgb = vec3_init(obj->r, obj->g, obj->b);
	if (!(obj->rgb))
	{
		free(obj->xyz);
		free(obj->norm);
		return (1);
	}
	return (0);
}

t_plane	*sub_build_plane(char **tbl, int to_switch, t_plane **obj)
{
	char		**vec;
	char		**rgb;
	double		coord_switch[3];
	double		coord_not_switch[3];

	vec = ft_split(tbl[2], ',');
	if (!vec || tbl_3_check(vec) || (!vec[0] || !vec[1] || !vec[2]))
		return (pl_cy_tbl_free(NULL, obj, &vec), NULL);
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, vec);
	if (to_switch)
		build_helper_2(&(((*obj))->vec_x), &((*obj)->vec_y), &((*obj)->vec_z), coord_switch);
	else
		build_helper_2(&((*obj)->vec_x), &((*obj)->vec_y), &((*obj)->vec_z), coord_not_switch);
	ft_freetbl(vec, -1);
	if (!(*obj)->vec_x && !(*obj)->vec_y && !(*obj)->vec_z)
		return (free(*obj), NULL);
	rgb = ft_split(tbl[3], ',');
	if (!rgb || tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
		return (pl_cy_tbl_free(NULL, obj, &rgb), NULL);
	rgb_helper(&((*obj)->r), &((*obj)->g), &((*obj)->b), rgb);
	ft_freetbl(rgb, -1);
	if (build_plane_vecs(*obj))
		return (free(*obj), NULL);
	return (*obj);
}

t_plane	*build_plane(char **tbl, int to_switch)
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
	return (sub_build_plane(tbl, to_switch, &obj));
}
