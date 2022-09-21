/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/21 05:04:25 by omoudni          ###   ########.fr       */
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
//	double	center_phit[3];
//	double	u_center_phit[3];
//	double	u_phit[3];

//	vec_subtract(hit->phit, pl->xyz, &center_phit);
//	vec_unit(center_phit, &u_center_phit);
//	vec_unit(hit->phit, &u_phit);
//	hit->u = (vec_dot(u_center_phit , pl->e1)) * 0.5 + 0.5;
//	hit->v = (vec_dot(u_center_phit, pl->e2)) * 0.5 + 0.5;

	hit->u = vec_dot(hit->phit, pl->e1);
	hit->v = vec_dot(hit->phit, pl->e2);
//	hit->u = vec_dot(u_phit, pl->e1);
//	hit->v = vec_dot(u_phit, pl->e2);
}

t_mat44	*mat44_init_utils(double angle_y, t_cylinder *cy)
{
	t_mat44	*ret;
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	
	a[0] = cos((angle_y  / 180) * M_PI);
//	printf("a[0]: %f\n", a[0]);
	a[1] = 0;
	a[2] = -sin((angle_y  / 180) * M_PI);
//	printf("a[2]: %f\n", a[2]);
	b[0] = 0;
	b[1] = 1;
	b[2] = 0;
	c[0] = sin((angle_y  / 180) * M_PI);
//	printf("c[0]: %f\n", c[0]);
	c[1] = 0;
	c[2] = cos((angle_y  / 180) * M_PI);
//	printf("c[2]: %f\n", c[2]);
	d[0] = - cy->xyz[0];
	d[1] = - cy->xyz[1];
	d[2] = - cy->xyz[2];
	ret = mat44_init(a, b, c, d); 
	return (ret);
}

void	trans_to_cy(double (*trans_phit)[3], double (*trans_cy)[3], t_cylinder *cy, t_hit *hit)
{
	double	s;
	double	c;
	double	b[3];
	double	v[3];
	double	c1[3];
	double	c2[3];
	double	c3[3];
	double	c4[3];
	t_mat44	*mat;

	vec_set(0, 1, 0, &b);
	vec_cross(cy->norm, b, &v);
	c = vec_dot(cy->norm, b);
	s = vec_len(v);
	s = (1 - c) / pow(s,2);
	vec_set(1, v[2] + pow(v[2], 2) * s, -v[1] + pow(-v[1], 2) * s, &c1);
	vec_set(-v[2] + pow(-v[2], 2) * s, 0, v[0] + pow(v[0], 2) * s, &c2);
	vec_set(v[1] + pow(v[1], 2) * s, -v[0] + pow(-v[0], 2) * s, 0, &c3);
	vec_set(-cy->xyz[0], -cy->xyz[1], -cy->xyz[2], &c4);
	mat = mat44_init(c1, c2, c3, c4);
	vec_matrix_multiply(mat, hit->phit, 1, trans_phit);
	vec_matrix_multiply(mat, cy->xyz,1,  trans_cy);

	
}

void	set_uv_cylinder(t_hit *hit, t_cylinder *cy)
{
	double	cy_center[3];
	double	xyz[3];
	double	cy_c[3];
	double	theta;
	double	raw_u;
	double	tot_y_cy;
//	double	trans_phit[3];

//	vec_ray_distance_to_point(cy->xyz, cy->norm, cy->height/2, &cy_center);
	vec_set(cy->xyz[0] , cy->xyz[1], cy->xyz[2], &cy_center);
//	printf("phit_x: %f, phit_y: %f, phit_z: %f\n", hit->phit[0], hit->phit[1], hit->phit[2]);
	trans_to_cy(&xyz, &cy_center, cy, hit);
//	printf("xyz: %f, xyz: %f, xyz: %f\n", xyz[0], xyz[1], xyz[2]);
//	vec_subtract(hit->phit, cy_center, &xyz);
	theta = atan(xyz[0] / xyz[2]);
	raw_u = theta / (2 * M_PI);
	hit->u = 1 - (raw_u + 0.5);
	tot_y_cy = cy_c[1] + cy->height;
	hit->v = (hit->phit[1] - cy_c[1]) / tot_y_cy;
	printf("==>u: %f, ==>v: %f\n", hit->u, hit->v);
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
	printf("u: %f, v: %f\n", hit->u, hit->v);
	printf("tex->w: %d, tex->h: %d, x: %d, y: %d\n", tex->w, tex->h, x, y);
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
