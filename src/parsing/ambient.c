/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/02 16:57:52 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* need to build atoi for doubles */

int	build_ambient(char **tbl, t_ambient **obj)
{
	char		**rgb;
	t_vec3		*tmp;

	(*obj) = malloc(sizeof(t_ambient));
	if (!(*obj))
		return (1);
	(*obj)->lighting_ratio = (double)ft_atod(tbl[1]);
	rgb = ft_split(tbl[2], ',');
	(*obj)->r = (size_t)ft_atoi(rgb[0]);
	(*obj)->g = (size_t)ft_atoi(rgb[1]);
	(*obj)->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	tmp = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
	(*obj)->rgb = vec3_multiply(tmp, (*obj)->lighting_ratio);
	free(tmp);
	return (0);
}
