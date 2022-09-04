/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:58:55 by swillis           #+#    #+#             */
/*   Updated: 2022/09/03 20:30:50 by swillis          ###   ########.fr       */
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
# include <math.h>

# define WIDTH 800
# define HEIGHT 600

# define ERROR_ARGS "Syntax not respected\nUse --help as an option for more information.\n"
# define HELP_MSG "usage: ./miniRT scene_file.rt\n"
# define ERROR_PARSING "Parsing error\n"

/* types of objects in linked list */

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
	int					type;
	void				*content;
	struct s_obj_lst	*next;
}	t_obj_lst;

/* identifier: A								 	*/
/* ambient lighting ratio in range [0.0,1.0]: 0.2	*/
/* R,G,B colors in range [0-255]: 255, 255, 255 	*/

typedef struct s_ambient
{
	double	lighting_ratio;
	size_t	r;
	size_t	g;
	size_t	b;
	t_vec3	*rgb;
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
	t_vec3	*xyz;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	t_vec3	*norm;
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
	t_vec3	*xyz;
	size_t	r;
	size_t	g;
	size_t	b;
	double	brightness_ratio;
	t_vec3	*rgb;
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
	t_vec3	*xyz;
	double	diameter;
	size_t	r;
	size_t	g;
	size_t	b;
	t_vec3	*rgb;
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
	t_vec3	*xyz;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	t_vec3	*norm;
	size_t	r;
	size_t	g;
	size_t	b;
	t_vec3	*rgb;
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
	t_vec3	*xyz;
	double	vec_x;
	double	vec_y;
	double	vec_z;
	t_vec3	*norm;
	double	diameter;
	double	height;
	size_t	r;
	size_t	g;
	size_t	b;
	t_vec3	*rgb;
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

/*	Space structure	*/

typedef struct s_space {
	t_camera	*camera;
	t_ambient	*ambient;
	t_obj_lst	*objects;
	size_t		n_lights;
	t_light		**lights;
}	t_space;

/*	Param structure	*/

typedef struct s_param {
	double		scale;
	double		aspect_ratio;
	double		px;
	double		py;
	size_t		colour;
}	t_param;

/*	Ray structure	*/

typedef struct s_ray {
	t_vec3	*origin;
	t_vec3	*direction;
}	t_ray;

/*	Hit structure	*/

typedef struct s_hit {
	double		t;
	t_obj_lst	*nearest;
	t_vec3		*phit;
	t_vec3		*rgb;
}	t_hit;

/* MLX */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	data;
	t_space	*space;
}	t_vars;

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */
/* ================== PARSING ====================== */
/* object_list.c */
int			obj_lstadd(t_obj_lst **lst, int type, t_object *object);
void		obj_lstfree(t_obj_lst **lst);

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
t_mat44		*camera_lookat(t_camera *cam);
t_vec3		*vec3_matrix_multiply(t_mat44 *mat, t_vec3 *vec, double w);

/* rays.c */
size_t		cast_ray(t_ray *ray, t_space *space, char *c);

/* =================== VISUALS ====================== */

/* mlx_render.c */
void		my_mlx_pixel_put(t_data *data, int px, int py, int color);
void		mlx_render(t_space *space);

/* sphere.c */
void		calc_c_dscr(double pxyz[3], double cxyz[3], t_sphere *sp, double *c);
double		get_dscr(t_vec3 *r_or, t_vec3 *r_dir, t_sphere *sp, double (*ab)[2]);
double		get_short_dist(double discriminant, double a, double b);
t_vec3		*hit_point(t_vec3 *r_origin, t_vec3 *r_direction, double t);
t_vec3		*hitpt_raysp(t_vec3 *r_or, t_vec3 *r_dir, t_sphere *sp);

/* =================== INTERSECTION ====================== */

/* light_intersection.c */
void		light_intersection(t_ray *ray, t_light *light, t_hit *hit);

/* sphere_intersection.c */
void		sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit);
t_vec3		*sphere_surface_normal(t_sphere *sphere, t_vec3 *phit);

/* plane_intersection.c */
void		plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit);
t_vec3		*plane_surface_normal(t_plane *plane, t_ray *ray);

/* =================== VISUALS ====================== */

/* space_render.c */
void		space_render(t_data *data, int width, int height, t_space *space);

/* =================== MAIN ====================== */

/* utils.c */
double		deg2rad(double degree);
void		print_progress(int i, int total);
size_t		rgb_colour(t_vec3 *rgb);
t_vec3		*rgb_multiply(t_vec3 *rgb1, t_vec3 *rgb2);

#endif
