/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:42:53 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 11:45:33 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	build_cylinder_vecs(t_cylinder **obj)
{
	t_cylinder	*cy;

	cy = *obj;
	vec_set(cy->x, cy->y, cy->z, &cy->xyz);
	vec_set(cy->vec_x, cy->vec_y, cy->vec_z, &cy->norm);
	vec_unit(cy->norm, &cy->norm);
	vec_set(cy->r, cy->g, cy->b, &cy->rgb);
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
	build_cylinder_vecs(&obj);
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
