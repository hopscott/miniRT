/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 00:36:49 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_swap_double(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}


void	cam_switch(t_camera *obj, int *to_switch)
{
	if(!(obj)->norm->e[0] && !(obj)->norm->e[2] && (obj)->norm->e[1] > 0)
	{
		ft_swap_double(&((obj)->norm->e[1]), &((obj)->norm->e[2]));
		ft_swap_double(&((obj)->xyz->e[1]), &((obj)->xyz->e[2]));
		*to_switch = 1;
	}
	if(!(obj)->norm->e[0] && !(obj)->norm->e[2] && (obj)->norm->e[1] < 0)
	{
		ft_swap_double(&((obj)->norm->e[1]), &((obj)->norm->e[2]));
		ft_swap_double(&((obj)->xyz->e[1]), &((obj)->xyz->e[2]));
		(obj)->norm->e[0] *= -1;
		(obj)->norm->e[1] *= -1;
		(obj)->xyz->e[0] *= -1;
		(obj)->xyz->e[1] *= -1;
		*to_switch = -1;
	}
}

void	build_helper(double *x, double *y, double *z, char **tab)
{
	*x = (double)ft_atod(tab[0]);
	*y = (double)ft_atod(tab[1]);
	*z = (double)ft_atod(tab[2]);
}

int		sub_build_cam(char *tbl_3, t_camera *obj, int *to_switch)
{
	t_vec3		*tmp;

	obj->fov = (size_t)ft_atoi(tbl_3);
	obj->xyz = vec3_init(obj->x, obj->y, obj->z);
	tmp = vec3_init(obj->vec_x, obj->vec_y, obj->vec_z);
	if (!(obj->xyz) || !tmp)
		return (1);
	obj->norm = vec3_unit(tmp, 1);
	if (!(obj->norm))
		return (1);
	cam_switch(obj, to_switch);
	return (0);
}


int	build_camera(char **tbl, t_camera *obj, int *to_switch)
{
	char		**xyz;
	char		**vec;

	xyz = ft_split(tbl[1], ',');
	if (!xyz || (tbl_3_check(xyz)) || (!xyz[0] || !xyz[1] || !xyz[2]))
		return (tbl_free(&xyz), 1);
	build_helper(&(obj->x), &(obj->y), &(obj->z), xyz);
	ft_freetbl(xyz, -1);
	vec = ft_split(tbl[2], ',');
	if (!vec || tbl_3_check(vec) || (!vec[0] || !vec[1] || !vec[2]))
		return (tbl_free(&vec), 1);
	build_helper(&(obj->vec_x), &(obj->vec_y), &(obj->vec_z), vec);
	ft_freetbl(vec, -1);
	if (!obj->vec_x && !obj->vec_y && !obj->vec_z)
		return (3);
	return (sub_build_cam(tbl[3], obj, to_switch));
}
