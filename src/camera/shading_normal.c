/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scottwillis <scottwillis@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/07 19:04:06 by scottwillis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ========================================================== */
/* https://computergraphics.stackexchange.com/questions/5498  */
/* /compute-sphere-tangent-for-normal-mapping				  */
/* ========================================================== */

void	tbn_tangents_sphere(t_hit *hit, double surface_norm[3], \
					double (*tangent)[3], double (*bitangent)[3])
{
	vec_set((-1 * hit->r * cos(hit->theta) * sin(hit->phi)), \
			0, \
			(hit->r * cos(hit->theta) * cos(hit->phi)), \
			tangent);
	vec_cross(surface_norm, (*tangent), bitangent);
}

void	tbn_tangents_plane(t_plane *plane, \
					double (*tangent)[3], double (*bitangent)[3])
{
	vec_copy(plane->e1, tangent);
	vec_copy(plane->e2, bitangent);
}

t_mat44	*mat44_init_tbn(t_hit *hit, double surface_norm[3], \
									int type, double bump_norm[3])
{
	double	tangent[3];
	double	bitangent[3];
	double	zeros[3];
	t_mat44	*ret;

	if (type == SPHERE)
		tbn_tangents_sphere(hit, surface_norm, &tangent, &bitangent);
	else if (type == PLANE)
		tbn_tangents_plane((t_plane *)hit->nearest->content, \
												&tangent, &bitangent);
	else if (type == CYLINDER)
		tbn_tangents_sphere(hit, surface_norm, &tangent, &bitangent);
	vec_set(0, 0, 0, &zeros);
	ret = mat44_init(tangent, bitangent, bump_norm, zeros);
	return (ret);
}

/* ========================================================= */
/* https://en.wikipedia.org/wiki/Normal_mapping 			 */
/* ========================================================= */
/* https://shader-tutorial.dev/intermediates/normal-mapping/ */
/* ========================================================= */

void	convert_color(unsigned char *color, double (*bump_norm)[3])
{
	double	rgb[3];

	vec_set((double)color[2], \
			(double)color[1], \
			(double)color[0], \
			&rgb);
	vec_set(2 * (rgb[0] / 255) - 1, \
			2 * (rgb[1] / 255) - 1, \
			(rgb[2] - 127 )/ 128, \
			bump_norm);
	if ((*bump_norm)[0] < (double)-1)
		(*bump_norm)[0] = -1;
	if ((*bump_norm)[0] > (double)1)
		(*bump_norm)[0] = 1;
	if ((*bump_norm)[1] < (double)-1)
		(*bump_norm)[1] = -1;
	if ((*bump_norm)[1] > (double)1)
		(*bump_norm)[1] = 1;
	if ((*bump_norm)[2] < (double)0)
		(*bump_norm)[2] = 0;
	if ((*bump_norm)[2] > (double)1)
		(*bump_norm)[2] = 1;
}

int	set_bump_normal(t_hit *hit, t_data *bump, int type, \
										double (*surface_norm)[3])
{
	t_mat44			*tbn;
	int				x;
	int				y;
	unsigned char	*color;
	double			bump_norm[3];

	x = (int)(hit->u * bump->w * bump->bpp / 8);
	x -= x % 4;
	y = (int)(hit->v * bump->h * bump->bpp / 8);
	y -= y % 4;
	color = (unsigned char *)(bump->addr + x + bump->w * y);
	convert_color(color, &bump_norm);
	tbn = mat44_init_tbn(hit, (*surface_norm), type, bump_norm);
	if (!tbn)
		return (1);
	// vec_print("before", *norm);
	vec_matrix_multiply(tbn, bump_norm, 1, surface_norm);
	free(tbn);
	// vec_print("bump", bump_norm);
	// vec_print("after", *norm);
	
	return (0);
}
