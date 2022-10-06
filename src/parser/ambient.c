/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/10/05 18:59:59 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	build_ambient(char **tbl, t_ambient *obj)
{
	char		**rgb;

	obj->lighting_ratio = (double)ft_atod(tbl[1]);
	rgb = ft_split(tbl[2], ',');
	if (tbl_3_check(rgb) || (!rgb[0] || !rgb[1] || !rgb[2]))
		return (tbl_free(&rgb), 1);
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	vec_set(obj->r, obj->g, obj->b, &obj->rgb);
	vec_multiply(obj->rgb, obj->lighting_ratio, &obj->rgb);
	return (0);
}
