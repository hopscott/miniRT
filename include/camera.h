/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/16 19:52:31 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"

typedef struct s_mat44 {
	double	a[4];
	double	b[4];
	double	c[4];
	double	d[4];
}			t_mat44;

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */
/* =================== CAMERA ====================== */
/* matrix.c */
t_mat44	*camera_lookat(t_camera *cam);
t_vec3	*vec3_matrix_multiply(t_mat44 *mat, t_vec3 *vec, double w);

/* ================================================= */


#endif