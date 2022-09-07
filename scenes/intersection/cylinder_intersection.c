/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:31:38 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/07 17:04:26 by swillis          ###   ########.fr       */
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

uint8_t	new_dist(double dist, t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy)
{
	t_vec3	*cy_point;
	t_vec3	*cy_center;
	t_vec3	*cy_center_middle;
	t_vec3	*cy_orient;
	double	dist_p_center;
	double	dist_max;
	double	radius;

	radius = cy->diameter / 2;
	cy_point = vec3_ray_distance_to_point(r_or, r_dir, dist);
	cy_center = vec3_init(cy->x, cy->y, cy->z);
	cy_orient = vec3_unit(vec3_init(cy->vec_x, cy->vec_y, cy->vec_z), 1);
	cy_center_middle = vec3_ray_distance_to_point(cy_center, cy_orient, cy->height / 2);
	dist_p_center = vec3_distance_points(cy_point, cy_center_middle);
	dist_max = sqrt(pow(cy->height / 2, 2) + pow(radius, 2));
	if (dist_p_center < dist_max)
		return (1);
	return (0);
}


double	find_smallest_dist(t_vec3 *r_or, t_vec3 *r_dir, t_cylinder *cy, double discr, double a, double b)
{
	double	dist1;
	double	dist2;
//	t_vec3	r_dir_unit;

	dist1 = (((- b + sqrt(discr)) / (2 * a)));
	dist2 = ((- b - sqrt(discr)) / (2 * a));
//	r_dir_unit = vec3_unit(r_dir, 0);
	//	printf("dist_1: %f\n", dist1);
	//	printf("dist_2: %f\n", dist2);
	if (dist1 < dist2)
	{
		if (new_dist(dist1, r_or, r_dir, cy))
			return (dist1);
		else if (new_dist(dist2, r_or, r_dir, cy)) 
			return (dist2);
	}
	else if (dist2 < dist1)
	{
		if (new_dist(dist2, r_or, r_dir, cy))
			return (dist2);
		else if (new_dist(dist1, r_or, r_dir, cy)) 
			return (dist1);
	}
	return (-1);
}
//c: (point)cylinder's center; h: (distance)height; ch: (vector)between c and hi
//cy_orient: (vector)cy_direct_vector_unit
//
//
void	cy_intersection(t_ray *ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	*center;
	t_vec3	*center_inv;
	t_vec3	*cy_orient_bef;
	t_vec3	*cy_orient;
	t_vec3	*rot_r_or;
	t_vec3	*rot_r_dir;
	double	a;
	double	b;
	double	c;
	double	radius;
	double	discr;
	double	smallest_dist;

	radius = cy->diameter / 2;
	center = vec3_init(cy->x - ray->origin->e[0], cy->y - ray->origin->e[1] ,cy->z - ray->origin->e[2]);
	center_inv = vec3_multiply(center, -1);
	cy_orient_bef = vec3_unit(vec3_init(cy->vec_x, cy->vec_y, cy->vec_z), 1);
//printf("rx: %f, ry: %f, rz: %f\n",cy->vec_x, cy->vec_y, cy->vec_z);
	cy_orient = cy_orient_bef;
	rot_r_dir = vec3_cross(ray->direction, cy_orient);
	rot_r_or = vec3_cross(center_inv, cy_orient);
	a = vec3_dot(rot_r_dir, rot_r_dir);
	b = 2 * vec3_dot(rot_r_dir, rot_r_or);
	c = vec3_dot(rot_r_or, rot_r_or) - pow(radius, 2);
	discr = pow(b, 2) - 4 * a * c;
	if (discr < 0)
		hit->t = -1;
	smallest_dist = find_smallest_dist(ray->origin, ray->direction, cy, discr, a, b);
	hit->t = smallest_dist;
}

t_vec3	*cylinder_surface_normal(t_cylinder * cy, t_vec3 *phit)
{
	double	t;
	t_vec3	*pt;
	t_vec3	*surface_normal;

    t = vec3_dot((vec3_subtract(phit, cy->xyz)), cy->norm); // cy.ori should be normalized and so has the length of 1.
    pt = vec3_ray_distance_to_point(cy->xyz, cy->norm, t);
    surface_normal = vec3_unit(vec3_subtract(phit, pt), 1);
	return (surface_normal);
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
   ch = vec3_ray_distance_to_point(c, cy_orient, cy->height);
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


