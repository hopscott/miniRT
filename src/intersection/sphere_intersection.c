/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/01 12:07:09 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//src: https://stackoverflow.com/questions/5883169/intersection-between-a-line-and-a-sphere
void	calc_c_dscr(double pxyz[3], double cxyz[3], t_sphere *sp, double *c)
{
	*c = pxyz[0] * pxyz[0] - 2 * pxyz[0] * cxyz[0] + cxyz[0] * cxyz[0]
		+ pxyz[1] * pxyz[1] - 2 * pxyz[1] * cxyz[1] + cxyz[1] * cxyz[1]
		+ pxyz[2] * pxyz[2] - 2 * pxyz[2] * cxyz[2] + cxyz[2] * cxyz[2]
		- pow(sp->diameter/2,2);
}

double	get_dscr(t_vec3 *r_or, t_vec3 *r_dir, t_sphere *sp, double (*ab)[2])
{
	double	abc[3];
	double	discriminant;
	t_vec3	*s_center;
	double	p_xyz[3];
	double	c_xyz[3];
	t_vec3	*vec_substr;

	p_xyz[0] = r_or->e[0];
	p_xyz[1] = r_or->e[1];
	p_xyz[2] = r_or->e[2];
	s_center = vec3_init(sp->x, sp->y, sp->z);
	c_xyz[0] = s_center->e[0];
	c_xyz[1] = s_center->e[1];
	c_xyz[2] = s_center->e[2];
	abc[0] = vec3_dot(r_dir, r_dir);
	vec_substr = vec3_subtract(r_or, s_center); // if malloc fails free everything and exit
	abc[1] = 2 * vec3_dot(vec_substr, r_dir);
	free(vec_substr);
	calc_c_dscr(p_xyz, c_xyz, sp, &(abc[2]));
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	(*ab)[0] = vec3_dot(r_dir, r_dir);
	vec_substr = vec3_subtract(r_or, s_center); // if malloc fails free everything and exit
	(*ab)[1] = 2 * vec3_dot(vec_substr, r_dir);
	free(vec_substr);
	free(s_center);
	return (discriminant);
}

double	get_short_dist(double discriminant, double a, double b)
{
	double	t1;
	double	t2;

	t1 = (-1 * b - sqrt(discriminant)) / (2 * a);
	t2 = (-1 * b + sqrt(discriminant)) / (2 * a);
	if (t1 <= t2)
		return (t1);
	return (t2);
}

t_vec3	*hit_point(t_vec3 *r_origin, t_vec3 *r_direction, double t)
{
	t_vec3	*ret;
	double	x;
	double	y;
	double	z;

	x = r_origin->e[0] * (1 - t) + t * (r_origin->e[0] + r_direction->e[0]);
	y = r_origin->e[1] * (1 - t) + t * (r_origin->e[1] + r_direction->e[1]);
	z = r_origin->e[2] * (1 - t) + t * (r_origin->e[2] + r_direction->e[2]);
	ret = vec3_init(x, y, z);
	if (!ret)
		return (NULL);
	return (ret);
}

double	sphere_intersection(t_vec3 *r_or, t_vec3 *r_dir, t_sphere *sp)
{
	double	ab[2];
	double	discriminant;
	double	t;

	discriminant = get_dscr(r_or, r_dir, sp, &ab);
	if (discriminant < 0)
		return (-1);
	t = get_short_dist(discriminant, ab[0], ab[1]);
	return (t);
}

/*
Function that directly finds the point of intersection, The one above was derived from it:
t_vec3	*hitpt_raysp(t_vec3 *r_or, t_vec3 *r_dir, t_sphere *sp)
{
	double	ab[2];
	double	discriminant;
	double	t;

	discriminant = get_dscr(r_or, r_dir, sp, &ab);
	if (discriminant < 0)
		return (NULL);
	t = get_short_dist(discriminant, ab[0], ab[1]);
	return (hit_point(r_or, r_dir, t));
}

//main for testing the function

int	main(int argc, char **argv)
{
	t_vec3		r_origin;
	t_vec3		r_direction;
	t_sphere	sphere;
	t_vec3		*hit_pt;

	r_origin.e[0] = 0;
	r_origin.e[1] = 0;
	r_origin.e[2] = -5;
	r_direction.e[0] = 0;
	r_direction.e[1] = 0;
	r_direction.e[2] = 1;
	sphere.x = 0;
	sphere.y = 0;
	sphere.z = 0;
	sphere.diameter = 2;
	hit_pt = hitpt_raysp(&r_origin, &r_direction, &sphere);
	printf("point:\nx: %f\ny: %f\nz: %f\n", hit_pt->e[0], hit_pt->e[1], hit_pt->e[2]);
	return (0);
}
*/
