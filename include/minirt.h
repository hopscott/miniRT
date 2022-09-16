/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:58:55 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 20:51:11 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec3.h"
# include "vec2.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdint.h>

# define WIDTH 1280
# define HEIGHT 1024

//#define WIDTH 40
//#define	HEIGHT 30

# define ERROR_ARGS "Syntax not respected\nUse --help as an option for more information.\n"
# define HELP_MSG "Usage: ./miniRT scene_file.rt\nCheck the README for more details about the parameters.\nCheck example.rt for the file layout.\n"
# define ERROR_PARSING "Corrupted file.\nUse --help as an option for more information.\n"
# define ERROR_PARAMS "None of the parameters required was introduced in .rt file.\nUse --help as an option for more information.\n"
# define FATAL_ERROR "\nFATAL ERROR!!!\n"


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

typedef struct s_cambient
{
	t_camera	*camera;
	t_ambient	*ambient;
}			t_cambient;

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
	t_vec3	*e1;
	t_vec3	*e2;
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
	t_vec3	*co;
	t_vec3	*cross_co_orient;
	double	radius;
	t_vec3	*rgb;
}			t_cylinder;

/*	Union object structure	*/
typedef union u_object {
	t_camera	c;
	t_ambient	a;
	t_light		l;
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}				t_object;

typedef struct s_arb_vecs {
	t_vec3	*v1;
	t_vec3	*v2;
	t_vec3	*v3;
}				t_arb_vecs;

/*	Space structure	*/
typedef struct s_space {
	t_camera	*camera;
	int			cam;
	t_ambient	*ambient;
	int			amb;
	t_obj_lst	*objects;
	size_t		n_lights;
	t_light		**lights;
	double		width;
	double		height;
	int			fatal_error;
	t_arb_vecs	*arb_vecs;
}	t_space;

/*	mat44 structure	*/
typedef struct s_mat44 {
	double	a[4];
	double	b[4];
	double	c[4];
	double	d[4];
}			t_mat44;

/*	Param structure	*/
typedef struct s_param {
	int			height;
	int			width;
	double		scale;
	double		aspect_ratio;
	t_mat44		*matrix;
	double		px;
	double		py;
	size_t		colour;
	char		**screen_hit;
	char		**screen_shading;
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
	size_t		colour;
	char		shading;
}	t_hit;

/*	Shade structure	*/
typedef struct s_shade {
	t_ray		*ray;
	t_object	*obj;
	t_object	*lobj;
	t_vec3		*rgb;
	t_vec3		*normal;
	t_vec3		*ambient;
	t_vec3		*diffuse;
	double		kd;
	double		diffuse_comp;
	t_vec3		*specular;
	double		ks;
	double		specular_comp;
}	t_shade;

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

/* ================== PRINTER ====================== */
/* printer.c */
void		print_space(t_space *space);

/* printer_utils.c */
void	print_columns(void);
void	print_ambient(t_ambient *amb);
void	print_camera(t_camera *cam);
void	print_light(t_light *l);

/* ================== PARSER ====================== */
/* object_list.c */
int			obj_lstadd(t_obj_lst **lst, int type, t_object *object);
void		obj_lstfree(t_obj_lst **lst);

/* errorinizer.c */
void		puterr_free(char *err, t_space *space);
void		print_help(void);

/* ambient.c */
int			build_ambient(char **tbl, t_ambient *obj);

/* camera.c */
int			build_camera(char **tbl, t_camera *obj, int *to_switch);

/* light.c */
t_light		*build_light(char **tbl, int to_switch);

/* sphere.c */
t_sphere	*build_sphere(char **tbl, int to_switch);

/* plane.c */
t_plane		*build_plane(char **tbl, int to_switch, t_space *space);
int			get_e1_e2(t_space *space, t_plane *plane);

/* cylinder.c */
t_cylinder	*build_cylinder(char **tbl, int to_switch);

/* parser.c */
int			parser(char *path, t_space *space, t_camera *camerat,t_ambient *ambient);
int			init_3_arb_vec3(t_space *space, t_arb_vecs *arb_vecs);

/* parser_utils.c */
int		init_parser_params(t_space *space);
int			check_space_null(t_space *space);
int			line_is_space(char *str);

/* parser_utils2.c */
int			tbl_3_check(char **tbl);
void		pl_cy_tbl_free(t_cylinder **cy, t_plane **p, char ***tbl);
void		tbl_free(char ***tbl);
int			dptr_len(char **tbl);
int			check_rt(char *path);

/* free_er.c */
void		free_space(t_space *space_ptr);
int			tbl_3_check(char **tbl);
void		tbl_free(char ***tbl);

/* utils.c */
void		rgb_helper(size_t *r, size_t *g, size_t *b, char **rgb);
void		get_switch_coord(double (*c_switch)[3], \
				double (*c_not_switch)[3], int to_switch, char **xyz);
void		build_helper_2(double *x, double *y, double *z, double coords[3]);

/* =================== CAMERA ====================== */

/* matrix.c */
t_mat44		*camera_lookat(t_camera *cam);
t_vec3		*vec3_matrix_multiply(t_mat44 *mat, t_vec3 *vec, double w);

/* rays.c */
size_t		cast_ray(t_ray *ray, t_space *space, char *object, char *shading);
int			nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit);

/* shading.c */
int			shading(t_space *space, t_ray *ray, t_hit *hit, t_object *object);

/* shading_light.c */
int			shading_from_light(t_space *sp, t_hit *h, t_light *l, t_shade *sh);

/* =================== VISUALIZER ====================== */

/* mlx_render.c */
void		my_mlx_pixel_put(t_data *data, int px, int py, int color);
void		mlx_render(t_space *space);

/* space_render.c */
void		space_render(t_data *data, int width, int height, t_space *space);

/* space_render_utils.c */
int			fatal_error_int(t_space *space);
void		fatal_error(t_space *space);
void		free_params(t_param *param);
void		print_screens_and_free_matrix(t_param *param);

/* =================== INTERSECTOR ====================== */

/* light_intersection.c */
int			light_intersection(t_ray *ray, t_light *light, t_hit *hit);

/* sphere_intersection.c */
int			sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit);
t_vec3		*sphere_surface_normal(t_ray *ray, t_sphere *sphere, t_vec3 *phit);

/* sphere_intersection_utils.c */
void		calc_c_dscr(double pxyz[3], double cxyz[3], t_sphere *sp, \
																	double *c);
void		get_dsc_helper(double (*p_xyz)[3], double (*c_xyz)[3], \
											t_vec3 *s_center, t_ray *ray);
double		*get_dscr_2(double **old_abc, t_sphere *sp, t_ray *r, t_vec3 **s_c);
double		*get_dscr(t_ray *r, t_sphere *sp);
double		get_short_dist(double discriminant, double a, double b);

/* plane_intersection.c */
int			plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit);
t_vec3		*plane_surface_normal(t_plane *plane, t_ray *ray);
t_vec3		*normal_bmap_plane_mountains(t_plane *plane, t_hit *hit);
t_vec3		*normal_bmap_plane_lines(t_plane *plane, t_hit *hit);
/* cylinder_intersection.c */
int			cy_intersection(t_ray *ray, t_cylinder *cy, t_hit *hit);
t_vec3		*cylinder_surface_normal(t_cylinder *cy, t_vec3 *phit);
int			adjust_plane_norm(t_obj_lst *space_objs, t_vec3 *r_or);

void		cy_init_cam_center(t_camera *camera, t_obj_lst **objs);

/* =================== MAIN ====================== */

/* utils.c */
double		deg2rad(double degree);
void		print_progress(int i, int total);
size_t		rgb_colour(t_vec3 *rgb);
void		rgb_multiply_to_self(t_vec3 **rgb1, t_vec3 *rgb2);
void		print_screen(char **screen);

#endif
