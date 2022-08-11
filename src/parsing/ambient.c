/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 22:28:10 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* need to build atoi for doubles */

t_ambient	*build_ambient(char **tbl)
{
	t_ambient	*obj;
	char		**rgb;

	obj = malloc(sizeof(t_ambient));
	if (!obj)
		return (NULL);
	obj->lighting_ratio = (double)ft_atoi(tbl[1]);
	rgb = ft_split(tbl[2], ',');
	obj->r = (size_t)ft_atoi(rgb[0]);
	obj->g = (size_t)ft_atoi(rgb[1]);
	obj->b = (size_t)ft_atoi(rgb[2]);
	ft_freetbl(rgb, -1);
	return (obj);
}
