/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:55:58 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/15 16:57:36 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cy_data {
	double	tmp[3];
	double	center[3];
	double	inv_center[3];
	double	cy_orient_bef[3];
	double	cy_orient[3];
	double	rot_r_r[3];
	double	rot_r_dir[3];
	double	a;
	double	b;
	double	c;
	double	radius;
	double	discr;
	double	smallest_dist;
}				t_cy_data;

#endif
