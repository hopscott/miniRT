/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 18:21:55 by omoudni          ###   ########.fr       */
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
/* utils.c */
t_vec3	*vec3_init(double a, double b, double c);
void	vec3_print(char *str, t_vec3 *vec);
t_vec3	*vec3_copy(t_vec3 *vec);
int		vec3_free_multi(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, int err);
void	vec3_free_multi2(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3);

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

/* extra_ops.c */
void	vec3_add_to_self(t_vec3 **vec, t_vec3 *new);
void	vec3_multiply_to_self(t_vec3 **vec, double t);
t_vec3	*vec3_ray_distance_to_point(t_vec3 *origin, t_vec3 *direction, double t);
int		check_vec3_null(t_vec3 *vec);

/* ================================================= */


#endif
