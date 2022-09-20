/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 23:51:16 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat44	*mat44_init_tbn(double phit_xyz[3], double norm[3], double bump_norm[3])
{
	t_mat44	*ret;
	double	tangent[3];
	double	bitangent[3];
	double	zeros[3];

	vec_set(0, 0, 0, &tangent);
	vec_set(0, 0, 0, &bitangent);
	vec_set(0, 0, 0, &zeros);
	ret = mat44_init(tangent, bitangent, bump_norm, zeros);
	return (ret);
}

int	set_bump_normal(t_hit *hit, t_data *bump, double (*norm)[3])
{
	t_mat44	*tbn;
	int		x;
	int		y;
	char	*color;
	double	bump_norm[3];

	x = (int)(hit->u * bump->w * bump->bpp / 8);
	y = (int)(hit->v * bump->h * bump->bpp / 8);
	color = bump->addr + x + bump->w * y;
	vec_set(2 * (double)color[0] - 1, \
			2 * (double)color[1] - 1, \
			2 * (double)color[2] - 1, \
			&bump_norm);
	tbn = mat44_init_tbn(hit->phit, *norm, bump_norm);
	if (!tbn)
		return (1);
}
