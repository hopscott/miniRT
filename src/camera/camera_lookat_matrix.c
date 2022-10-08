/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_lookat_mat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:55:57 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/05 16:57:07 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat44	*camera_lookat(t_camera *cam)
{
	double	fwd[3];
	double	arb[3];
	double	right[3];
	double	up[3];
	double	coord[3];

	if (!cam)
		return (NULL);
	vec_copy(cam->norm, &fwd);
	vec_set(0, 1, 0, &arb);
	vec_unit(arb, &arb);
	vec_cross(arb, fwd, &right);
	vec_unit(right, &right);
	vec_cross(fwd, right, &up);
	vec_unit(up, &up);
	vec_set(-vec_dot(right, cam->xyz), -vec_dot(up, cam->xyz), \
			-vec_dot(fwd, cam->xyz), &coord);
	return (mat44_init(right, up, fwd, coord));
}
