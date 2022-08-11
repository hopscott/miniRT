/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/11 21:49:48 by swillis          ###   ########.fr       */
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

/*	Union object structure	*/

typedef union u_object {
	t_ambient	a;
	t_camera	c;
	t_light		l;
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;	
}				t_object;

/* ************* */
/* * Functions * */
/* ************* */
/* ==================== PARSING ======================= */
/* linked_list.c */
t_list		*ft_lstnew(int type, void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
/* ambient.c */
t_ambient	*build_ambient(char **tbl);
/* camera.c */
t_camera	*build_camera(char **tbl);
/* light.c */
t_light		*build_light(char **tbl);
/* sphere.c */
t_sphere	*build_sphere(char **tbl);
/* plane.c */
t_plane		*build_plane(char **tbl);
/* cylinder.c */
t_cylinder	*build_cylinder(char **tbl);
/* parser.c */
int			parser(char *path, t_list **lst);
void		ft_print_objects(t_list **lst);
/* ==================================================== */

#endif
