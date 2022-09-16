/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:03:34 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/16 17:46:06 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ============================================ */
/* https://stackoverflow.com/questions/5883169/ */
/* intersection-between-a-line-and-a-sphere		*/
/* ============================================ */

void	free_double_vec3(double **abc, t_vec3 **vec3)
{
	if (*abc)
		free(abc);
	if (*vec3)
		free(vec3);
}

void	get_dsc_helper(double (*p_xyz)[3], double (*c_xyz)[3], \
											t_vec3 *s_center, t_ray *ray)
{
	(*p_xyz)[0] = ray->origin->e[0];
	(*p_xyz)[1] = ray->origin->e[1];
	(*p_xyz)[2] = ray->origin->e[2];
	(*c_xyz)[0] = s_center->e[0];
	(*c_xyz)[1] = s_center->e[1];
	(*c_xyz)[2] = s_center->e[2];
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
	vec_substr = vec3_subtract(r->origin, *s_center);
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
	vec_substr = vec3_subtract(r->origin, s_center);
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
