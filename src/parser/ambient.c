/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/12 22:29:30 by omoudni          ###   ########.fr       */
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
	if (tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
		return (tbl_free(&rgb), 1);
	(*obj)->r = (size_t)ft_atoi(rgb[0]);
	(*obj)->g = (size_t)ft_atoi(rgb[1]);
	(*obj)->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	tmp = vec3_init((*obj)->r, (*obj)->g, (*obj)->b);
	if (!tmp)
		return (1);
	(*obj)->rgb = vec3_multiply(tmp, (*obj)->lighting_ratio);
	if (!((*obj)->rgb))
		return (free(tmp), 1);
	free(tmp);
	return (0);
}
