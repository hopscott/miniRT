/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:37:33 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/18 20:54:08 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

# include "libft.h"

typedef struct s_vec2 {
	double	x;
	double	y;
}				t_vec2;

typedef struct s_cercle {
	double	radius;
	t_vec2	center;
}				t_cercle;

#endif
