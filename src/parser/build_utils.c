/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 16:50:45 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rgb_helper(size_t *r, size_t *g, size_t *b, char **rgb)
{
	*r = (size_t)ft_atoi(rgb[0]);
	*g = (size_t)ft_atoi(rgb[1]);
	*b = (size_t)ft_atoi(rgb[2]);
}

void	get_switch_coord(double (*c_switch)[3], \
			double (*c_not_switch)[3], int to_switch, char **xyz)
{
	if (to_switch)
	{
		(*c_switch)[0] = to_switch * (double)ft_atod(xyz[0]);
		(*c_switch)[1] = to_switch * (double)ft_atod(xyz[2]);
		(*c_switch)[2] = (double)ft_atod(xyz[1]);
	}
	else
	{
		(*c_not_switch)[0] = (double)ft_atod(xyz[0]);
		(*c_not_switch)[1] = (double)ft_atod(xyz[1]);
		(*c_not_switch)[2] = (double)ft_atod(xyz[2]);
	}
}

void	build_helper_2(double *x, double *y, double *z, double coords[3])
{
	*x = coords[0];
	*y = coords[1];
	*z = coords[2];
}
