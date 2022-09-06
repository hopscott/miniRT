/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:38:57 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/31 02:14:21 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double cylinder_intersection(t_vec3 *orig, t_vec3 *dir, t_cylinder *cyl)
{
	t_vec3	dir_2d;
	double	tp;
	t_vec3	cyl_center;
//	t_vec3	*cp;
	t_vec3	*cp;
	double	alpha;
	double	tc;
	double	ti;
	double	ip;
	double	cos_beta;
	double	pp_p;
	t_vec3	pp;
	double	rd_magn;
	double	cp_magn;

	dir_2d.e[0] = dir->e[0];
	dir_2d.e[1] = 0;
	dir_2d.e[2] = dir->e[2];
	cyl_center.e[0] = cyl->x;
	cyl_center.e[1] = cyl->y;
	cyl_center.e[2] = cyl->z;
	cp = vec3_subtract(orig, &cyl_center);
	rd_magn = vec3_lensq(&dir_2d);
	cp_magn = vec3_lensq(cp);
//	printf("\nor_x: %f, or_y: %f, or_z:%f\n", orig->e[0], orig->e[1], orig->e[2]);
//	printf("\ncyl_x: %f, cyl_y: %f, cyl_z:%f\n",cyl_center.e[0],cyl_center.e[1], cyl_center.e[2]);
//	printf("\ncyl_x: %f, cyl_y: %f, cyl_z:%f\n",cyl->x,cyl->y, cyl->z);
//	cp = vec3_subtract(orig, &cyl_center);
	tp = vec3_dot(&dir_2d, cp) / (rd_magn * cp_magn);
	//printf("\ncp_x: %f, cp_y: %f, cp_z:%f\n",cp->e[0],cp->e[1], cp->e[2]);
	printf("\ndir_x: %f, dir_y: %f, dir_z:%f\n",dir_2d.e[0],dir_2d.e[1], dir_2d.e[2]);
	printf("\ntp: %f\n",tp);
//	exit(0);
	alpha = acos(tp);
	printf("alpha: %f\n", alpha);
	tc = sin(alpha) *cp_magn;
	ti = sqrt(pow(cyl->diameter / 2, 2) - pow(tc, 2));
	printf("ti: %f\n", ti);
	ip = tp - ti;
	cos_beta = vec3_dot(dir, cp) / (vec3_lensq(dir) * cp_magn);
	printf("cos_beta: %f\n", cos_beta);
	printf("ip: %f\n", ip);

	pp_p = ip / cos_beta;
	printf("dist: %f\n", pp_p);
	pp.e[0] = orig->e[0] + dir->e[0] * pp_p;
	pp.e[1] = orig->e[1] + dir->e[1] * pp_p;
	pp.e[2] = orig->e[2] + dir->e[2] * pp_p;
	if (tc <= cyl->r)
		return (pp_p);
	return (-1);
}
