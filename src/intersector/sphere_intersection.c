/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/15 20:22:57 by omoudni          ###   ########.fr       */
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

void	get_dsc_helper(double (*p_xyz)[3], double (*c_xyz)[3], t_vec3 *s_center, t_ray *ray)
{
	(*p_xyz)[0] = ray->origin->e[0];
	(*p_xyz)[1] = ray->origin->e[1];
	(*p_xyz)[2] = ray->origin->e[2];
	(*c_xyz)[0] = s_center->e[0];
	(*c_xyz)[1] = s_center->e[1];
	(*c_xyz)[2] = s_center->e[2];
}

void	free_double_vec3(double **abc, t_vec3 **vec3)
{
	if (*abc)
		free(abc);
	if (*vec3)
		free(vec3);
}

double	*get_dscr_2(double **old_abc, t_sphere *sp, t_ray *r, t_vec3 **s_center)
{
	double	*ab_dsc;
	double	*abc;
	double	p_xyz[3];
	double	c_xyz[3];
	t_vec3	*vec_substr;

	abc = *old_abc;
	ab_dsc = malloc(3 * sizeof(double));
	if (!ab_dsc)
		return (NULL);
	get_dsc_helper(&p_xyz, &c_xyz, *s_center, r);
	calc_c_dscr(p_xyz, c_xyz, sp, &(abc[2]));
	ab_dsc[2] = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	vec_substr = vec3_subtract(r->origin, *s_center); // if malloc fails free everything and exit
	if (!vec_substr)
		return (free_double_vec3(old_abc, s_center), NULL);
	ab_dsc[0] = vec3_dot(r->direction, r->direction);
	ab_dsc[1] = 2 * vec3_dot(vec_substr, r->direction);
	free(vec_substr);
	free(*s_center);
	free(*old_abc);
	return (ab_dsc);
}

double	*get_dscr(t_ray *r, t_sphere *sp)
{
	double	*abc;
	t_vec3	*s_center;
	double	p_xyz[3];
	double	c_xyz[3];
	t_vec3	*vec_substr;

	abc = malloc(3 * sizeof(double));
	if (!abc)
		return (NULL);
	s_center = vec3_init(sp->x, sp->y, sp->z);
	if (!s_center)
		return (free(abc), NULL);
	get_dsc_helper(&p_xyz, &c_xyz, s_center, r);
	vec_substr = vec3_subtract(r->origin, s_center); // if malloc fails free everything and exit
	if (!vec_substr)
		return (free_double_vec3(&abc, &s_center), NULL);
	abc[0] = vec3_dot(r->direction, r->direction);
	abc[1] = 2 * vec3_dot(vec_substr, r->direction);
	free(vec_substr);
	return (get_dscr_2(&abc, sp, r, &s_center));
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

int	sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	double	*abc_dsc;
	double	discriminant;

	abc_dsc = get_dscr(ray, sp);
	if (!abc_dsc)
		return (1);
	discriminant = abc_dsc[2];
	if (discriminant < 0)
		hit->t = -1;
	else
		hit->t = get_short_dist(discriminant, abc_dsc[0], abc_dsc[1]);
	free(abc_dsc);
	return (0);
}

t_vec3	*sphere_surface_normal(t_ray *ray, t_sphere *sphere, t_vec3 *phit)
{
	t_vec3	*tmp;
	t_vec3	*normal;

	if (vec3_distance_points(ray->origin, sphere->xyz) < sphere->diameter / 2)
		tmp = vec3_subtract(sphere->xyz, phit);
	else
		tmp = vec3_subtract(phit, sphere->xyz);
	if (!tmp)
		return (NULL);
	normal = vec3_unit(tmp, 1);
	if (!normal)
		return (free(tmp), NULL);
	return (normal);
}
