/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/04 00:25:23 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ========================================================== */
/* https://computergraphics.stackexchange.com/questions/5498  */
/* /compute-sphere-tangent-for-normal-mapping				  */
/* ========================================================== */

t_mat44	*mat44_init_tbn(t_hit *hit, double norm[3], double bump_norm[3])
{
	t_mat44	*ret;
	double	tangent[3];
	double	bitangent[3];
	double	zeros[3];
	double	r;
	double	theta;
	double	phi;

	r = vec_len(hit->phit);
	theta = ((2 * M_PI) + 0.5) * (1 - (hit->u / 2));
	phi = M_PI * (1 - hit->v);
	vec_set((-r * cos(theta) * sin(phi)), \
			0, \
			(r * cos(theta) * cos(phi)), \
			&tangent);
	vec_cross(norm, tangent, &bitangent);
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
	tbn = mat44_init_tbn(hit, (*norm), bump_norm);
	if (!tbn)
		return (1);
	vec_matrix_multiply(tbn, (*norm), 0, norm);
	free(tbn);
	return (0);
}
