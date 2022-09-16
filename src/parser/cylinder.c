/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 17:00:18 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_cylinder_vecs(t_cylinder **obj)
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
	return (0);
}

t_cylinder	*sub_build_cy(char **tbl, int to_switch, t_cylinder **cy, \
															char ***tmp)
{
	t_cylinder	*obj;
	double		coord_switch[3];
	double		coord_not_switch[3];

	obj = *cy;
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, *tmp);
	if (to_switch)
		build_helper_2(&(obj->vec_x), &(obj->vec_y), \
											&(obj->vec_z), coord_switch);
	else
		build_helper_2(&(obj->vec_x), &(obj->vec_y), \
										&(obj->vec_z), coord_not_switch);
	ft_freetbl(*tmp, -1);
	if (!(obj->vec_x) && !(obj->vec_y) && !(obj->vec_z))
		return (free(obj), NULL);
	obj->diameter = (double)ft_atod(tbl[3]);
	obj->height = (double)ft_atod(tbl[4]);
	*tmp = ft_split(tbl[5], ',');
	if (!*tmp || tbl_3_check(*tmp) || (!(*tmp)[0] || !(*tmp)[1] || !(*tmp)[2]))
		return (pl_cy_tbl_free(cy, NULL, tmp), NULL);
	rgb_helper(&(obj->r), &(obj->g), &(obj->b), *tmp);
	ft_freetbl(*tmp, -1);
	if (build_cylinder_vecs(&obj))
		return (free(obj), NULL);
	return (obj);
}

t_cylinder	*build_cylinder(char **tbl, int to_switch)
{
	t_cylinder		*obj;
	char			**tmp;
	double			coord_switch[3];
	double			coord_not_switch[3];

	obj = malloc(sizeof(t_cylinder));
	if (!obj)
		return (NULL);
	tmp = ft_split(tbl[1], ',');
	if (!tmp || tbl_3_check(tmp) || (!tmp[0] || !tmp[1] || !tmp[2]))
		return (pl_cy_tbl_free(&obj, NULL, &tmp), NULL);
	get_switch_coord(&coord_switch, &coord_not_switch, to_switch, tmp);
	if (to_switch)
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_switch);
	else
		build_helper_2(&(obj->x), &(obj->y), &(obj->z), coord_not_switch);
	ft_freetbl(tmp, -1);
	tmp = ft_split(tbl[2], ',');
	if (!tmp || tbl_3_check(tmp) || (!tmp[0] || !tmp[1] || !tmp[2]))
		return (pl_cy_tbl_free(&obj, NULL, &tmp), NULL);
	return (sub_build_cy(tbl, to_switch, &obj, &tmp));
}
