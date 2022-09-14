/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 02:45:07 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_light_vecs(t_light **obj)
{
	t_vec3	*tmp;

	(*obj)->xyz = vec3_init((*obj)->x, (*obj)->y, (*obj)->z);
	if (!((*obj)->xyz))
		return (1);
	tmp = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
	if (!tmp)
		return (free((*obj)->xyz), 1);
	(*obj)->rgb = vec3_multiply(tmp, (*obj)->brightness_ratio);
	free(tmp);
	if (!((*obj)->rgb))
		return (free((*obj)->xyz), 1);
	return (0);
}

void	rgb_helper(size_t *r, size_t *g, size_t *b, char **rgb)
{
	*r = (size_t)ft_atoi(rgb[0]);
	*g = (size_t)ft_atoi(rgb[1]);
	*b = (size_t)ft_atoi(rgb[2]);
}

void	get_switch_coord(double (*c_switch)[3], double (*c_not_switch)[3], int to_switch, char **xyz)
{

	if (to_switch)
	{
		(*c_switch)[0] = to_switch * (double)ft_atod(xyz[0]);
		(*c_switch)[1] = to_switch * (double)ft_atod(xyz[2]);
		(*c_switch)[2] =(double)ft_atod(xyz[1]);
	}
	else
	{
		(*c_not_switch)[0] = (double)ft_atod(xyz[0]);
		(*c_not_switch)[1] = (double)ft_atod(xyz[1]);
		(*c_not_switch)[2] = (double)ft_atod(xyz[2]);
	}
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
	if (build_light_vecs(&obj))
		return (free(obj), NULL);
	return (obj);
}

void	build_helper_2(double *x, double *y, double *z, double coords[3])
{
	*x = coords[0];
	*y = coords[1];
	*z = coords[2];
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
