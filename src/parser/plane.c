/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 18:44:30 by omoudni          ###   ########.fr       */
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

t_plane	*build_plane(char **tbl, int to_switch)
{
	t_plane		*obj;
	char		**xyz;
	char		**vec;
	char		**rgb;

	obj = malloc(sizeof(t_plane));
	if (!obj)
		return (NULL);
	xyz = ft_split(tbl[1], ',');
	if (!xyz || tbl_3_check(xyz) || (!xyz[0] || !xyz[1] || !xyz[2]))
		return (free_tbl(&xyz), NULL);
	obj->x = (double)ft_atod(xyz[0]);
	if (to_switch)
	{
		obj->x = to_switch * (double)ft_atod(xyz[0]);
		obj->y = to_switch *(double)ft_atod(xyz[2]);
		obj->z = (double)ft_atod(xyz[1]);
	}
	else
	{
		obj->y = (double)ft_atod(xyz[1]);
		obj->z = (double)ft_atod(xyz[2]);
	}
	ft_freetbl(xyz, -1);
	vec = ft_split(tbl[2], ',');
	if (!vec || tbl_3_check || (!vec[0] || !vec[1] || !vec[2]))
		return (tbl_free(&vec), NULL);
	obj->vec_x = (double)ft_atod(vec[0]);
	if (to_switch)
	{
		obj->vec_y = (double)ft_atod(vec[2]);
		obj->vec_z = (double)ft_atod(vec[1]);
	}
	else
	{
		obj->vec_y = (double)ft_atod(vec[1]);
		obj->vec_z = (double)ft_atod(vec[2]);
	}

	ft_freetbl(vec, -1);
	rgb = ft_split(tbl[3], ',');
	if (!rgb || tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
		return (tbl_free(&rgb), NULL);
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	if (build_plane_vecs(obj))
		return (free(obj), NULL);
	return (obj);
}
