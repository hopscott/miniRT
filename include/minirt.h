/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:58:55 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 17:34:21 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec.h"
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

# define ERROR_ARGS "Syntax not respected\nUse \
--help as an option for more information.\n"
# define HELP_MSG "Usage: ./miniRT scene_file.rt\nCheck the README \
for more details about the parameters.\nCheck example.rt for the file layout.\n"
# define ERROR_PARSING "Corrupted file.\nUse --help as an option \
for more information.\n"
# define ERROR_PARAMS "None of the parameters required was introduced \
in .rt file.\nUse --help as an option for more information.\n"
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

enum {
	NONE		= 0,
	CHECKERS	= 1,
	TEXTURE		= 2,
	BUMP		= 3,
	BUMPTEXT	= 4,
};

/* Use void pointers in linked list to build up objects */

typedef struct s_obj_lst
{
	int					type;

	void				*content;
	int					surface;
	struct s_obj_lst	*next;
}	t_obj_lst;

typedef struct s_ambient
{
	double	lighting_ratio;
	size_t	r;
	size_t	g;
	size_t	b;
	double	rgb[3];
}			t_ambient;

typedef struct s_camera
{
	double	x;
	double	y;
	double	z;
	double	xyz[3];
	double	vec_x;
	double	vec_y;
	double	vec_z;
	double	norm[3];
	size_t	fov;
}			t_camera;

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
	double	xyz[3];
	size_t	r;
	size_t	g;
	size_t	b;
	double	brightness_ratio;
	double	rgb[3];
}			t_light;

typedef struct s_sphere
{
	double	x;
	double	y;
	double	z;
	double	xyz[3];
	double	diameter;
	size_t	r;
	size_t	g;
	size_t	b;
	double	rgb[3];
}			t_sphere;

typedef struct s_plane
{
	double	x;
	double	y;
	double	z;
	double	xyz[3];
	double	vec_x;
	double	vec_y;
	double	vec_z;
	double	norm[3];
	size_t	r;
	size_t	g;
	size_t	b;
	double	rgb[3];
	double	e1[3];
	double	e2[3];
}			t_plane;

typedef struct s_cylinder
{
	double	x;
	double	y;
	double	z;
	double	xyz[3];
	double	vec_x;
	double	vec_y;
	double	vec_z;
	double	norm[3];
	size_t	r;
	size_t	g;
	size_t	b;
	double	rgb[3];
	double	diameter;
	double	height;
	double	radius;
	double	co[3];
	double	cross_co_orient[3];
	double	norm_magnitude;
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
	double	v1[3];
	double	v2[3];
	double	v3[3];
}				t_arb_vecs;

/* MLX */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_data;

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
	t_arb_vecs	arb_vecs;
	t_data		*texture;
}	t_space;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	data;
	t_data	texture;
	t_space	*space;
}	t_vars;

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
	double	origin[3];
	double	direction[3];
}	t_ray;

/*	Hit structure	*/
typedef struct s_hit {
	double		t;
	t_obj_lst	*nearest;
	double		phit[3];
	double		rgb[3];
	size_t		colour;
	char		shading;
	double		u;
	double		v;
}	t_hit;

/*	Shade structure	*/
typedef struct s_shader {
	t_ray		*ray;
	t_object	*obj;
	t_object	*lobj;
	double		rgb[3];
	double		normal[3];
	double		ambient[3];
	double		diffuse[3];
	double		kd;
	double		diffuse_comp;
	double		specular[3];
	double		ks;
	double		specular_comp;
	t_data		*texture;
}	t_shader;

/* ************************************************* */
/* ***************** FUNCTIONS ********************* */
/* ************************************************* */

/* ================== PRINTER ====================== */
/* printer.c */
void		print_space(t_space *space);

/* printer_utils.c */
void		print_columns(void);
void		print_ambient(t_ambient *amb);
void		print_camera(t_camera *cam);
void		print_light(t_light *l);

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
t_plane		*build_plane(t_space *space, char **tbl, int to_switch);

/* cylinder.c */
t_cylinder	*build_cylinder(char **tbl, int to_switch);

/* parser.c */
int			parser(char *path, t_space *space, t_camera *camerat, \
													t_ambient *ambient);
int			init_3_arb_vec3(t_space *space, t_arb_vecs *arb_vecs);

/* parser_utils.c */
void		init_parser_params(t_space *space);
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
t_mat44		*mat44_init(double a[3], double b[3], double c[3], double d[3]);
t_mat44		*camera_lookat(t_camera *cam);
void		vec_matrix_multiply(t_mat44 *mat, double vec[3], double w, \
															double (*res)[3]);
/* rays.c */
size_t		cast_ray(t_ray *ray, t_space *space, char *object, char *shading);
void		nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit);

/* shading.c */
void		shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj);

/* shading_light.c */
void		shading_from_light(t_space *space, t_hit *hit, \
									t_light *light, t_shader *shader);

/* shading_uv.c */
void		set_uv_sphere(t_hit *hit, t_sphere *sp);
void		set_uv_plane(t_hit *hit, t_plane *pl);
void		set_uv_cylinder(t_hit *hit, t_cylinder *cy);

/* shading_rgb.c */
void		set_checkerboard_rgb(t_hit *hit, double surf_rgb[3], \
									double size, double (*rgb)[3]);
void		set_texture_rgb(t_hit *hit, t_data *tex, double (*rgb)[3]);
void		set_rgb(t_hit *hit, double rgb[3], double size, t_shader *shader);
void		surface_rgb_normal(t_hit *hit, t_object *obj, t_shader *shader);

/* =================== VISUALIZER ====================== */

/* mlx_render.c */
void		my_mlx_pixel_put(t_data *data, int px, int py, int color);
void		mlx_render(t_space *space);

/* space_render.c */
void		space_render(t_data *data, int width, int height, t_space *space);

/* space_render_utils.c */
void		fatal_error(t_space *space);
void		free_params(t_param *param);
void		print_screens_and_free_matrix(t_param *param);

/* =================== INTERSECTOR ====================== */

/* light_intersection.c */
int			light_intersection(t_ray *ray, t_light *light, t_hit *hit);

/* sphere_intersection.c */
void		sphere_intersection(t_ray *ray, t_sphere *sp, t_hit *hit);
void		sphere_surface_normal(t_ray *ray, t_sphere *sphere, double phit[3], \
															double (*norm)[3]);

/* plane_intersection.c */
int			plane_intersection(t_ray *ray, t_plane *plane, t_hit *hit);
int			plane_surface_normal(t_plane *plane, t_ray *ray, double vec[3]);
int			normal_bmap_plane_mountains(t_plane *pl, t_hit *hit, double v[3]);
int			normal_bmap_plane_lines(t_plane *plane, t_hit *hit, double vec[3]);

/* cylinder_intersection.c */
int			cy_intersection(t_ray *ray, t_cylinder *cy, t_hit *hit);
void		cylinder_surface_normal(t_cylinder *cy, double phit[3], \
															double (*norm)[3]);
void		adjust_plane_norm(t_obj_lst *space_objs, double r_or[3]);

void		cy_init_cam_center(t_camera *camera, t_obj_lst **objs);

/* =================== MAIN ====================== */

/* utils.c */
double		deg2rad(double degree);
void		print_progress(int i, int total);
size_t		rgb_colour(double rgb[3]);
void		rgb_multiply(double rgb1[3], double rgb2[3], double (*rgb)[3]);
void		print_screen(char **screen);

#endif
