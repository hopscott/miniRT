/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:38 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/01 18:44:41 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//w: (vector)pc with p the origin of the ray; c: (point)center of the cylinder
double	*find_abc(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy, t_vec3 *ch_unit)
{
	double	*ret;
	double	a;
	double	b;
	double	c_d;
	t_vec3	*w;
	t_vec3	*c;

	ret = (double *)malloc(3 * sizeof(double));
	if (!ret)
		return (NULL);
	c = vec3_init(cy->x, cy->y, cy->z);
	w = vec3_subtract(c, r_or);
	printf("w_x: %f, w_y: %f, w_z: %f\n", w->e[0], w->e[1], w->e[2]);
	a = vec3_dot(r_dir, r_dir) - pow(vec3_dot(r_dir, ch_unit), 2);
	b = 2 * (vec3_dot(r_dir, w) - vec3_dot(r_dir, ch_unit) * vec3_dot(w, ch_unit));
	c_d = vec3_dot(w, w) - pow(vec3_dot(w, ch_unit), 2) - pow(cy->diameter / 2, 2);
	ret[0] = a;
	ret[1] = b;
	ret[2] = c_d;
	return (ret);
}

double	find_smallest_dist(double discr, double a, double b)
{
	double	dist1;
	double	dist2;

	dist1 = (- b + sqrt(discr)) / (2 * a);
	dist2 = (- b - sqrt(discr)) / (2 * a);
	printf("dist_1: %f\n", dist1);
	printf("dist_2: %f\n", dist2);
	if (dist1 < dist2)
		return (dist1);
	return (dist2);
}

//c: (point)cylinder's center; h: (distance)height; ch: (vector)between c and hi
//cy_orient: (vector)cy_direct_vector_unit
double	cy_intersection(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy)
{
	t_vec3	*c;
	t_vec3	*cy_orient;
	t_vec3	*ch;
	t_vec3	*ch_unit;
	double	*abc;
	double	discr;
	double	a;
	double	b;
	double	c_d;
	double	dist;
	
	c = vec3_init(cy->x, cy->y, cy->z);
	cy_orient = vec3_init(cy->vec_x, cy->vec_y, cy->vec_z);
	ch = vec_from_or_vec_len(c, cy_orient, cy->height);
	ch_unit = vec3_unit(ch, 1);
	printf("ch_x: %f, ch_y: %f, ch_z: %f\n", ch_unit->e[0], ch_unit->e[1], ch_unit->e[2]);
	abc = find_abc(r_or, r_dir, cy, ch_unit);
	a = abc[0];
	printf("a: %f\n", a);
	b = abc[1];
	printf("b: %f\n", b);
	c_d = abc[2];
	printf("c: %f\n", c_d);
	discr = pow(b, 2) - 4 * a * c_d;
	printf("discr: %f\n", discr);
	if (discr <= 0)
		return (-1);
	dist = find_smallest_dist(discr, a, b);
	return (dist);
}
