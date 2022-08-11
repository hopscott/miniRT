/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 17:15:43 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

/* type of objects in linked list */

enum {
	ERROR		= -1,
	AMBIENT		= 0,
	CAMERA		= 1,
	LIGHT		= 2,
	SPHERE		= 3,
	PLANE		= 4,
	CYLINDER	= 5
};

/* Use void pointers in linked list to build up objects */

typedef struct s_list
{
	int				type;
	void			*content;
	struct s_list	*next;
}			t_list;

/* identifier: A								 	*/
/* ambient lighting ratio in range [0.0,1.0]: 0.2	*/
/* R,G,B colors in range [0-255]: 255, 255, 255 	*/

typedef struct s_ambient
{
	double	lighting_ratio;
	size_t	r;
	size_t	g;
	size_t	b;
}			t_ambient;

/* identifier: C 												*/
/* x,y,z coordinates of the view point: 0.0,0.0,20.6 			*/
/* 3d normalized orientation vector.					 		*/
/* In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0 			*/
/* FOV : Horizontal field of view in degrees in range [0,180] 	*/

typedef struct s_camera
{
	double	x;
	double	y;
	double	z;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	size_t	fov;
}			t_camera;

/* identifier: L 												*/
/* x,y,z coordinates of the light point: 0.0,0.0,20.6			*/
/* the light brightness ratio in range [0.0,1.0]: 0.6	 		*/
/* (not mandatory)R,G,B colors in range [0-255]: 10, 0, 255 	*/

typedef struct s_light
{
	double	x;
	double	y;
	double	z;
	double	brightness_ratio;
	size_t	r;
	size_t	g;
	size_t	b;
}			t_light;

/* identifier: sp											*/
/* x,y,z coordinates of the sphere center: 0.0,0.0,20.6		*/
/* the sphere diameter: 12.6								*/
/* R,G,B colors in range [0-255]: 10, 0, 255			 	*/

typedef struct s_sphere
{
	double	x;
	double	y;
	double	z;
	double	diameter;
	size_t	r;
	size_t	g;
	size_t	b;
}			t_sphere;

/* identifier: pl										*/
/* x,y,z coordinates: 0.0,0.0,-10.0						*/
/* 3d normalized orientation vector. 					*/
/* In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0		*/
/* R,G,B colors in range [0-255]: 0, 0, 255		 		*/

typedef struct s_plane
{
	double	x;
	double	y;
	double	z;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	size_t	r;
	size_t	g;
	size_t	b;
}			t_plane;

/* identifier: cy										*/
/* x,y,z coordinates: 50.0,0.0,20.6						*/
/* 3d normalized orientation vector.  					*/
/* In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0		*/
/* the cylinder diameter: 14.2					 		*/
/* the cylinder height: 21.42					 		*/
/* R,G,B colors in range [0,255]: 10, 0, 255	 		*/

typedef struct s_cylinder
{
	double	x;
	double	y;
	double	z;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	double	diameter;
	double	height;
	size_t	r;
	size_t	g;
	size_t	b;
}			t_cylinder;

/* ************* */
/* * Functions * */
/* ************* */

t_list	**parser(char *path);

#endif
