/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/25 16:31:45 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "libft.h"

typedef struct s_vec3 {
	double	e[3];
}			t_vec3;

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */
/* ==================== VEC3 ======================= */
/* init.c */
t_vec3	*vec3_init(double a, double b, double c);
void	vec3_print(t_vec3 *vec);

/* basic_ops.c */
t_vec3	*vec3_add(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*vec3_subtract(t_vec3 *vec1, t_vec3 *vec2);
t_vec3	*vec3_multiply(t_vec3 *vec1, double n);
t_vec3	*vec3_divide(t_vec3 *vec1, double n);
double	vec3_dot(t_vec3 *vec1, t_vec3 *vec2);

/* adv_ops.c */
t_vec3	*vec3_cross(t_vec3 *vec1, t_vec3 *vec2);
double	vec3_len(t_vec3 *vec);
double	vec3_lensq(t_vec3 *vec);
t_vec3	*vec3_unit(t_vec3 *vec1, int free);
double	vec3_distance_points(t_vec3 *vec1, t_vec3 *vec2);
/* ================================================= */


#endif
