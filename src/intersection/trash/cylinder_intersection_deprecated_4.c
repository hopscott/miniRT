/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:38 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/02 18:52:46 by omoudni          ###   ########.fr       */
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
//	printf("w_x: %f, w_y: %f, w_z: %f\n", w->e[0], w->e[1], w->e[2]);
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
//
double	cy_intersection(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy)
{
	t_vec3	*l0;
	t_vec3	*c0;
	t_vec3	*dl;
	t_vec3	*dc;
	t_vec3	*new_dc;
	t_vec3	*new_dc_2;
	t_vec3	*cy_orient;
	double	r;
	t_vec3	*e;
	double	e_utils;
	t_vec3	*f;
	double	f_utils;
	t_vec3	*l0c0;
	double	a;
	double	b;
	double	c;
	double	discr;
	double	dist;
	double	dir_len;
	
	r = cy->diameter / 2;
	c0 = vec3_init(cy->x, cy->y, cy->z);
	cy_orient = vec3_init(cy->vec_x, cy->vec_y, cy->vec_z);
	l0 = r_or; 
	dl = r_dir;
	dc = vec_from_or_vec_len(c0, cy_orient, cy->height);
	l0c0 = vec3_subtract(l0, c0);
	e_utils = vec3_dot(dl, dc) / vec3_dot(dc, dc);
	f_utils = vec3_dot(l0c0, dc) / vec3_dot(dc, dc);
	new_dc = vec3_init(e_utils * dc->e[0], e_utils * dc->e[1], e_utils * dc->e[2]);
	new_dc_2 = vec3_init(f_utils * dc->e[0], f_utils * dc->e[1], f_utils * dc->e[2]);
	e = vec3_subtract(dl, new_dc);
	f = vec3_subtract(l0c0, new_dc_2);
	a = vec3_dot(e, e);
	b = 2 * vec3_dot(e, f);
	c = vec3_dot(f, f) - pow(r, 2);
	discr = pow(b, 2) - 4 * a * c;
	if (discr <= 0)
		return (-1);
	dist = find_smallest_dist(discr, a, b);
	dir_len = vec3_len(r_dir);
	return (dir_len * dist);
}

//old version - to delete I think
/*
double	cy_intersection_1(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy)
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
*/


// main to test
/*
 *
int	main()
{
	t_vec3	*r_or;
	t_vec3	*dir;
	t_cylinder	cy;
	double		dist;

	r_or = vec3_init(0, 0, 3);
	dir = vec3_init(0, 1, -1);
	cy.x = 0;
	cy.y = 0;
	cy.z = 0;
	cy.diameter = 2;
	cy.height = 3;
	cy.vec_x = 0;
	cy.vec_y = 1;
	cy.vec_z = 0;
	dist = cy_intersection(r_or, dir, &cy);
	printf("dist: %f\n", dist);
	return (0);
}
*/
