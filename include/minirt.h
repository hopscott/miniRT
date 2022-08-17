/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:31:50 by swillis           #+#    #+#             */
/*   Updated: 2022/08/17 22:37:12 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec3.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

# define ERROR_ARGS "Syntax not respected\nUse --help as an option for more information.\n"
# define HELP_MSG "usage: ./miniRT scene_file.rt\n"
# define ERROR_PARSING "Parsing error\n"

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

typedef struct s_obj_lst
{
	int				type;
	void			*content;
	struct s_obj_lst	*next;
}			t_obj_lst;

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

/*	Light list structure	*/

typedef struct s_light_lst {
	t_light				*light;
	struct s_light_lst	*next;
}	t_light_lst;

/*	Space structure	*/

typedef struct s_space {
	t_camera	*camera;
	t_ambient	*ambient;
	t_light_lst	*lights;
	t_obj_lst	*objects;
}	t_space;

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */
/* ================== PARSING ====================== */
/* object_list.c */
int			obj_lstadd(t_obj_lst **lst, int type, t_object *object);
void		obj_lstfree(t_obj_lst **lst);

/* light_list.c */
int			light_lstadd(t_light_lst **lights, t_light *light);
void		light_lstfree(t_light_lst **lst);

/* errorinizer.c */
void		putstr_error(char *err);
void		print_help(void);

/* ambient.c */
int			build_ambient(char **tbl, t_ambient **obj);

/* camera.c */
int			build_camera(char **tbl, t_camera **obj);

/* light.c */
t_light		*build_light(char **tbl);

/* sphere.c */
t_sphere	*build_sphere(char **tbl);

/* plane.c */
t_plane		*build_plane(char **tbl);

/* cylinder.c */
t_cylinder	*build_cylinder(char **tbl);

/* parser.c */
int			parser(char *path, t_space *space);
void		print_space(t_space *space);

/* ================================================= */

#endif
