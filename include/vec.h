/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:51:37 by swillis           #+#    #+#             */
/*   Updated: 2022/09/19 17:28:48 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stdio.h>
# include <math.h>

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */

/* ==================== VEC3 ======================= */

/* utils.c */

void	vec_set(double a, double b, double c, double (*vec)[3]);
void	vec_copy(double vec[3], double (*res)[3]);
void	vec_ray_distance_to_point(double origin[3], double direction[3], \
													double t, double (*res)[3]);
double	vec_distance_points(double pt1[3], double pt2[3]);
void	vec_print(char *str, double vec[3]);

/* basic_ops.c */

void	vec_add(double vec1[3], double vec2[3], double (*res)[3]);
void	vec_subtract(double vec1[3], double vec2[3], double (*res)[3]);
void	vec_multiply(double vec[3], double n, double (*res)[3]);
void	vec_divide(double vec[3], double n, double (*res)[3]);
double	vec_dot(double vec1[3], double vec2[3]);

/* adv_ops.c */

double	vec_lensq(double vec[3]);
double	vec_len(double vec[3]);
void	vec_unit(double vec[3], double (*res)[3]);
void	vec_cross(double vec1[3], double vec2[3], double (*res)[3]);

/* ================================================= */

#endif
