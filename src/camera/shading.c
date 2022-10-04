/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/10/04 20:32:41 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ======================================================== */
/* https://en.wikipedia.org/wiki/Spherical_coordinate_system */
/* ======================================================== */

void	set_uv_sphere(t_hit *hit, t_sphere *sp)
{
	double	xyz[3];
	double	r;
	double	theta;
	double	phi;

	vec_subtract(hit->phit, sp->xyz, &xyz);
	r = vec_len(xyz);
	theta = acos(xyz[0] / r);
	phi = atan(xyz[2] / xyz[1]);
	if (xyz[0] < 0)
	{
		if (xyz[1] >= 0)
			phi += M_PI;
		else
			phi -= M_PI;
	}
	if (xyz[0] == 0)
	{
		if (xyz[1] >= 0)
			phi = M_PI;
		else
			phi = -M_PI;
	}
	hit->u = (1 - ((theta / (2 * M_PI)) + 0.5));
	hit->v = (1 - (phi / M_PI)) / 2;
	hit->u = fabs(hit->u);
	hit->v = fabs(hit->v);
	//	printf("u_sp: %f, v_sp: %f\n", hit->u, hit->v);
}

/* ======================================================== */
/* http://raytracerchallenge.com/bonus/texture-mapping.html */
/* ======================================================== */

void	set_uv_plane(t_hit *hit, t_plane *pl)
{
	hit->u = vec_dot(hit->phit, pl->e1);
	hit->v = vec_dot(hit->phit, pl->e2);
}

t_mat44	*mat44_init_utils(double angle_y, t_cylinder *cy)
{
	t_mat44	*ret;
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];

	a[0] = cos((angle_y  / 180) * M_PI);
	a[1] = 0;
	a[2] = -sin((angle_y  / 180) * M_PI);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin((angle_y  / 180) * M_PI);
	c[1] = 0;
	c[2] = cos((angle_y  / 180) * M_PI);
	d[0] = - cy->xyz[0];
	d[1] = - cy->xyz[1];
	d[2] = - cy->xyz[2];
	ret = mat44_init(a, b, c, d); 
	return (ret);
}

t_mat44	*set_rx(double	angle)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*r_x;

	a[0] = 1;
	a[1] = 0;
	a[2] = 0;
	b[0] = 0;
	b[1] = cos(angle);
	b[2] = sin(angle);
	c[0] = 0;
	c[1] = -sin(angle);
	c[2] = cos(angle);
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	r_x = mat44_init(a, b, c, d);
	return (r_x);
}

t_mat44	*set_ry(double	angle)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*r_y;

	a[0] = cos(angle);
	a[1] = 0;
	a[2] = -sin(angle);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin(angle);
	c[1] = 0;
	c[2] = cos(angle);
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	r_y = mat44_init(a, b, c, d);
	return (r_y);
}

t_mat44	*set_rz(double	angle)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*r_z;

	a[0] = cos(angle);
	a[1] = sin(angle);
	a[2] = 0;
	b[0] = -sin(angle);
	b[1] = cos(angle);
	b[2] = 0;
	c[0] = 0;
	c[1] = 0;
	c[2] = 1;
	d[0] = 0;
	d[1] = 0;
	d[2] = 0;
	r_z = mat44_init(a, b, c, d);
	return (r_z);
}

t_mat44	*set_t(t_cylinder *cy)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*t;

	a[0] = 1; 
	a[1] = 0; 
	a[2] = 0; 
	b[0] = 0; 
	b[1] = 1; 
	b[2] = 0; 
	c[0] = 0; 
	c[1] = 0; 
	c[2] = 1; 
	d[0] = - cy->xyz[0];  
	d[1] = - cy->xyz[1];
	d[2] = - cy->xyz[2];
	t = mat44_init(a, b, c, d);
	return (t);
}

t_mat44	*set_rot_mat(double phi, double theta)
{
	t_mat44	*r_y;
	t_mat44	*r_z;
	t_mat44	*r;

	r_y = set_ry(phi);
	r_z = set_rz(theta);
	r = mat_x_mat(r_z, r_y, 1);
	return (r);
}

t_mat44	*set_tr_mat(double phi, double theta)
{
	t_mat44	*rot_mat;

	rot_mat = set_rot_mat(phi, theta);
	return (rot_mat);
}

int	check_tr(t_cylinder *cy, t_mat44 *tr_mat)
{
	double	extr_pt[3];
	double	res[3];

	vec_matrix_multiply(tr_mat, cy->norm, 0, &res);
	printf("cy->norm : %f %f %f\n", cy->norm[0], cy->norm[1], cy->norm[2]);
	printf("cy->norm transformed:\n");
	printf("x_t: %f, y_t: %f, z_t: %f\n", res[0] , res[1], res[2]);
	vec_ray_distance_to_point(cy->xyz, res, cy->height, &extr_pt);
	printf("The top of the cylinder transformed:\n");
	printf("x_t: %f, y_t: %f, z_t: %f\n", extr_pt[0], extr_pt[1], extr_pt[2]);
/*
	if (!(res[0] < 0.0001 && res[2] < 0.0001 && res[1] >= 0.999999))
		return (1);
	else
		printf("Good transformation\n");
*/
	return (0);
}

int	get_n(double dx, double dy, int i)
{
	printf("i: %d, dx: %f, dy: %f\n", i, dx, dy);
	if (dy > 0)
	{
		if (dx > 0)
			return (0);
		else
			return (2);
	}
	else
		return (1);
}

double	grad_to_rad(double grad)
{
	double	rad;

	rad = grad * (M_PI / 200);
	return (rad);
}

double	get_gisement(double dx, double dy, int i)
{
	printf("i: %d, dx: %f, dy: %f\n",i, dx, dy);
	if (dx < EPSILON && dy < EPSILON)
		return (0);
	if (dx < EPSILON)
	{
		if (dy > 0)
			return (0);
		else
			return (grad_to_rad(200));
	}
	if (dy < EPSILON)
	{
		if (dx > 0)
			return (grad_to_rad(100));
		else
			return (grad_to_rad(300));
	}
	printf("get_n_blabla: %d\n", get_n(dx, dy, i));
//	printf("i: %d, dx: %f, dy: %f\n", i, dx, dy);
	return (atan(dy / dx) + get_n(dx,dy, i) * 200);
}

int	trans_to_cy(double (*trans_phit)[3], t_cylinder *cy, t_hit *hit)
{
	double	phi;
	double	theta;
	t_mat44	*tr_mat;

//	phi = get_gisement(cy->norm[2], cy->norm[0], 1);
//	theta = get_gisement(cy->norm[0], cy->norm[1], 2);	
//	phi = (M_PI / 2) - atan(cy->norm[1] / cy->norm[0]);
//	theta = atan(sqrt(pow(cy->norm[0], 2) + pow(cy->norm[1], 2)) / cy->norm[2]);
	phi = (M_PI - 2.3561944901923) + M_PI + (M_PI / 2); 
	theta = 0.95531661812451;
//	https://keisan.casio.com/exec/system/1359533867
	printf("---------------------\n");
	printf("phi: %f, theta: %f\n", phi, theta);
	tr_mat = set_tr_mat(phi, theta);
	check_tr(cy, tr_mat);
//	exit(0);
//	if (check_tr(cy, tr_mat))
//	{
//		free(tr_mat);
//		angle *= -1;
//		tr_mat = set_tr_mat(phi, cy);
//		double	extr_pt[3];
//		double	res[3];
//
//		vec_ray_distance_to_point(cy->xyz, cy->norm, cy->height, &extr_pt);
////		vec_matrix_multiply(tr_mat, extr_pt, 1, &res);
//		vec_matrix_multiply(tr_mat, cy->norm, 1, &res);
//		printf("cy->norm : %f %f %f\n", cy->norm[0], cy->norm[1], cy->norm[2]);
////		printf("The top of the cylinder transformed:\n");
//		printf("cy->norm transformed:\n");
//		printf("x_t: %f, y_t: %f, z_t: %f\n", res[0], res[1], res[2]);
//	}
//	exit (0);
	vec_matrix_multiply(tr_mat, hit->phit, 1, trans_phit);
	return (0);
}

void	set_uv_cylinder(t_hit *hit, t_cylinder *cy)
{
	double	xyz[3];
	double	theta;
	double	raw_u;
	double	tot_y_cy; //should be equal to height
	int		test;

	test = trans_to_cy(&xyz, cy, hit);
	if (test)
	{
		xyz[0] = hit->phit[0];
		xyz[1] = hit->phit[1];
		xyz[2] = hit->phit[2];
	}
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = (1 - (raw_u + 0.5));
	tot_y_cy = cy->height;
	hit->v = ((xyz[1] - cy->xyz[1]) / tot_y_cy) / 4;
//	exit(0);
}

/*
   void	set_checkerboard_rgb_cy(t_hit *hit, double surf_rgb[3], double size, double (*rgb)[3], t_data *tex)
   {
//	int		u2;
//	int		v2;
//	double	ncheckers_width;
//	double	ncheckers_height;
//	double	max[3];

(void)tex;
ncheckers_width = size;
ncheckers_height = size;
u2 = floor(hit->u * ncheckers_width);
v2 = floor(hit->v * ncheckers_height);
if ((u2 + v2) % 2 == 0)
vec_copy(surf_rgb, rgb);
else
{
vec_set(255, 255, 255, &max);
vec_subtract(max, surf_rgb, rgb);
}
}
*/

void	set_texture(t_hit *hit, double (*rgb)[3], t_data *tex)
{
	int	x;
	int	y;
	char	*color;
	double	rgb_pix[3];

	if (hit->u < 0)
		hit->u = 0;
	if (hit->u > 1)
		hit->u = 1;
	if (hit->v < 0)
		hit->v = 0;
	if (hit->v > 1)
		hit->v = 1;
	//	printf("bpp: %d\n", tex->bpp);
	x = (int)(hit->u * tex->w* tex->bpp/8);
	x -= x % 4;
	y = (int)(hit->v * tex->h * tex->bpp/8);
	y -= y % 4;
	//	printf("u: %f, v: %f\n", hit->u, hit->v);
	//	printf("tex->w: %d, tex->h: %d, x: %d, y: %d\n", tex->w, tex->h, x, y);
	color = tex->addr + x + tex->w * y;
	rgb_pix[0] = (double)color[2];
	rgb_pix[1] = (double)color[1];
	rgb_pix[2] = (double)color[0];
	//	if (!rgb_pix[0] && !rgb_pix[1] && !rgb_pix[2])
	vec_copy(rgb_pix, rgb);
}


void	set_checkerboard_rgb(t_hit *hit, double surf_rgb[3], double size, double (*rgb)[3])
{
	//	int		u2;
	//	int		v2;
	int		u2;
	int		v2;
	double	ncheckers_width;
	double	ncheckers_height;
	double	max[3];

	ncheckers_width = size;
	ncheckers_height = size;
	u2 = floor(hit->u * ncheckers_width);
	v2 = floor(hit->v * ncheckers_height);
	//	u2 = hit->u * ncheckers_width;
	//	v2 = hit->v * ncheckers_height;
	//	printf("u2: %f, v2: %f\n", u2, v2);
	if ((u2 + v2) % 2  == 0)
		vec_copy(surf_rgb, rgb);
	else
	{
		vec_set(255, 255, 255, &max);
		vec_subtract(max, surf_rgb, rgb);
	}
}



void	surface_rgb_normal(t_hit *hit, t_object *obj, t_ray *r, t_shade *shade, t_data *tex)
{
	(void)tex;
	shade->ray = r;
	shade->obj = obj;
	if (hit->nearest)
	{
		if (hit->nearest->type == SPHERE)
		{
			// vec_copy(obj->sp.rgb, &shade->rgb);
			set_uv_sphere(hit, &obj->sp);
			set_texture(hit, &shade->rgb, tex);
			//			printf("=> u: %f => v: %f \n", hit->u, hit->v);
			//			set_checkerboard_rgb(hit, obj->sp.rgb, 20, &shade->rgb);
			sphere_surface_normal(r, &obj->sp, hit->phit, &shade->normal);
		}
		else if (hit->nearest->type == PLANE)
		{
			set_uv_plane(hit, &obj->pl);
			set_texture(hit, &shade->rgb, tex);
			set_checkerboard_rgb(hit, obj->pl.rgb, 0.1, &shade->rgb);
			// vec_copy(obj->sp.rgb, &shade->rgb);
			vec_copy(obj->pl.norm, &shade->normal);
		}
		else if (hit->nearest->type == CYLINDER)
		{
			set_uv_cylinder(hit, &obj->cy);
			set_checkerboard_rgb(hit, obj->pl.rgb, 100, &shade->rgb);
//			set_texture(hit, &shade->rgb, tex);
//			vec_copy(obj->cy.rgb, &shade->rgb);
			cylinder_surface_normal(&obj->cy, hit->phit, &shade->normal);
		}
	}
}

void	init_light_components(t_space *space, t_shade *shade)
{
	t_ambient	*amb;

	amb = space->ambient;
	vec_multiply(amb->rgb, amb->lighting_ratio, &shade->ambient);
	shade->kd = 0.8;
	shade->diffuse_comp = 0;
	vec_set(0, 0, 0, &shade->diffuse);
	shade->ks = 0.15;
	shade->specular_comp = 0;
	vec_set(0, 0, 0, &shade->specular);
}

void	set_shading_char(t_shade *shade, t_hit *hit)
{
	if (shade->lobj == shade->obj)
	{
		if ((shade->specular_comp > shade->diffuse_comp))
		{
			if (shade->specular_comp > 0.01)
				hit->shading = '*';
		}
		else if (shade->diffuse_comp > 0.9)
			hit->shading = 'o';
	}
	else
		hit->shading = 'x';
}

/* https://www.scratchapixel.com/code.php?id=32&origin=/	*/
/* lessons/3d-basic-rendering/phong-shader-BRDF				*/
void	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj, t_data *tex)
{
	t_shade		shade;
	t_light		*light;
	size_t		i;

	surface_rgb_normal(hit, obj, ray, &shade, tex);
	init_light_components(space, &shade);
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		shading_from_light(space, hit, light, &shade);
		set_shading_char(&shade, hit);
	}
	vec_copy(shade.ambient, &hit->rgb);
	vec_add(hit->rgb, shade.diffuse, &hit->rgb);
	vec_add(hit->rgb, shade.specular, &hit->rgb);
	rgb_multiply(hit->rgb, shade.rgb, &hit->rgb);
}
