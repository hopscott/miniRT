/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:05:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/05 16:06:05 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat44	*mat44_init_utils(double angle_y, t_cylinder *cy)
{
	t_mat44	*ret;
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];

	a[0] = cos((angle_y  / 180) * M_PI);
	a[1] = 0;
	a[2] = -sin((angle_y  / 180) * M_PI);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin((angle_y  / 180) * M_PI);
	c[1] = 0;
	c[2] = cos((angle_y  / 180) * M_PI);
	d[0] = - cy->xyz[0];
	d[1] = - cy->xyz[1];
	d[2] = - cy->xyz[2];
	ret = mat44_init(a, b, c, d); 
	return (ret);
}

t_mat44	*set_rot_mat(double phi, double theta)
{
	t_mat44	*r_y;
	t_mat44	*r_z;
	t_mat44	*r;

	r_y = set_ry(phi);
	r_z = set_rz(theta);
	r = mat_x_mat(r_z, r_y, 1);
	return (r);
}
