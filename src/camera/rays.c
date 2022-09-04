/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/05 01:35:15 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes */

// Vec3f castRay(
//     const Vec3f &orig, const Vec3f &dir,
//     const std::vector<std::unique_ptr<Object>> &objects)
// {
//     Vec3f hitColor = 0;
//     const Object *hitObject = nullptr;  //this is a pointer to the hit object
//     float t;  //this is the intersection distance from the ray origin to the hit point
//     if (trace(orig, dir, objects, t, hitObject)) {
//         Vec3f Phit = orig + dir * t;
//         Vec3f Nhit;
//         Vec2f tex;
//         hitObject->getSurfaceData(Phit, Nhit, tex);
//         // Use the normal and texture coordinates to shade the hit point.
//         // The normal is used to compute a simple facing ratio and the texture coordinate
//         // to compute a basic checker board pattern
//         float scale = 4;
//         float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
//         hitColor = std::max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
//     }
//     return hitColor;
// }

void	nearest_hit_object(t_ray *ray, t_obj_lst *elem, t_hit *hit)
{
	double		tmin;
	t_object	*obj;

	hit->nearest = NULL;
	tmin = INFINITY;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == LIGHT)
			light_intersection(ray, &obj->l, hit);
		else if (elem->type == SPHERE)
			sphere_intersection(ray, &obj->sp, hit);
		else if (elem->type == PLANE)
			plane_intersection(ray, &obj->pl, hit);
		else if (elem->type == CYLINDER)
		{	
			//printf("\nor_x: %f, or_y: %f, or_z:%f\n", origin->e[0], origin->e[1], origin->e[2]);
//			printf("\ncyl_x: %f, cyl_y: %f, cyl_z:%f\n",(obj->cy).x,(obj->cy).y, (obj->cy).z);
			hit->t = cy_intersection(origin, direction, &obj->cy);
			printf("t: %f\n", t);
//			if (t > -1)
//				printf("\nI found a cylinder. here is the t to it: %f\n", t);
			nearest_ho_utils(&nearest, elem, &tmin, t);
		}
			;
		if ((hit->t >= 0.000001) && (hit->t < tmin))
		{
			hit->nearest = elem;
			tmin = hit->t;
		}
		elem = elem->next;
	}
	hit->t = tmin;
}

t_vec3	*ray_to_point(t_ray *ray, double t)
{
	t_vec3	*dist;
	t_vec3	*xyz;

	dist = vec3_multiply(ray->direction, t);
	xyz = vec3_add(ray->origin, dist);
	free(dist);
	return (xyz);
}

// PHONG REFLECTION
// We use the Phong illumation model int the default case. 
// The phong model is composed of a diffuse and a specular reflection component. 
//                 Vec3f lightAmt = 0, specularColor = 0; 
//                 Vec3f shadowPointOrig = (dotProduct(dir, N) < 0) ? 
//                     hitPoint + N * options.bias : 
//                     hitPoint - N * options.bias; 
// Loop over all lights in the scene and sum their contribution up 
// We also apply the lambert cosine law here though we haven't explained yet what this means. 
//                 for (uint32_t i = 0; i < lights.size(); ++i) { 
//                     Vec3f lightDir = lights[i]->position - hitPoint; 
//                     // square of the distance between hitPoint and the light
//                     float lightDistance2 = dotProduct(lightDir, lightDir); 
//                     lightDir = normalize(lightDir); 
//                     float LdotN = std::max(0.f, dotProduct(lightDir, N)); 
//                     Object *shadowHitObject = nullptr; 
//                     float tNearShadow = kInfinity; 
//                     // is the point in shadow, 
//					   // and is the nearest occluding object closer to the object than the light itself?
//                     bool inShadow = trace(shadowPointOrig, lightDir, objects, tNearShadow, index, uv, &shadowHitObject) && 
//                         tNearShadow * tNearShadow < lightDistance2; 
//                     lightAmt += (1 - inShadow) * lights[i]->intensity * LdotN; 
//                     Vec3f reflectionDirection = reflect(-lightDir, N); 
//                     specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, dir)), hitObject->specularExponent) * lights[i]->intensity; 
//                 } 
//                 hitColor = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks; 
//                 break; 

/* https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector */

t_vec3	*reflection_vector(t_vec3 *direction, t_vec3 *normal)
{
	double	dot;
	t_vec3	*vec;
	t_vec3	*reflection;

	dot = vec3_dot(direction, normal);
	vec = vec3_multiply(normal, (2 * dot));
	reflection = vec3_subtract(direction, vec);
	free(vec);
	return (reflection);
}

void	shading_v1(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_vec3		*rgb;
	t_vec3		*normal;
	t_vec3		*tmp;
	t_vec3		*amb;
	t_vec3		*spec;
	t_vec3		*reflection_dir;
	t_ray		lray;
	t_hit		lhit;
	t_object	*lobj;
	t_light		*light;
	size_t		i;

	rgb = NULL;
	normal = NULL;
	if (hit->nearest->type == SPHERE)
	{
		rgb = obj->sp.rgb;
		normal = sphere_surface_normal(&obj->sp, hit->phit);
	}
	else if (hit->nearest->type == PLANE)
	{
		rgb = obj->pl.rgb;
		normal = plane_surface_normal(&obj->pl, ray);
	}
	else if (hit->nearest->type == CYLINDER)
		;
	amb = vec3_copy(space->ambient->rgb);
	spec = vec3_init(0, 0, 0);
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];
		lray.origin = light->xyz;
		tmp = vec3_subtract(hit->phit, light->xyz);
		lray.direction = vec3_unit(tmp, 1);
		nearest_hit_object(&lray, space->objects, &lhit);
		if (lhit.nearest)
		{
			lobj = (t_object *)(lhit.nearest->content);
			if (lobj == obj)
			{
				tmp = vec3_multiply(light->rgb, vec3_dot(lray.direction, normal));
				vec3_add_to_self(&amb, tmp);
				free(tmp);
			}
		}
		reflection_dir = reflection_vector(lray.direction, normal);
		tmp = vec3_multiply(light->rgb, -vec3_dot(reflection_dir, ray->direction));
		vec3_add_to_self(&spec, tmp);
		free(tmp);
		free(reflection_dir);
	}
	tmp = rgb_multiply(rgb, amb);
	hit->rgb = vec3_add(tmp, spec);
	vec3_free_multi(amb, spec, tmp);
	free(normal);
}

char	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_vec3		*rgb;
	t_vec3		*normal;
	t_vec3		*ambient;
	t_vec3		*diffuse;
	t_vec3		*specular;
	double		albedo;
	t_vec3		*tmp;
	t_ray		lray;
	t_hit		lhit;
	t_object	*lobj;
	t_light		*light;
	size_t		i;
	t_vec3 		*r;
	t_vec3 		*v;
	double		kd;
	double		ks;
	int			n;
	char 		c;

	// init rgb + normal
	rgb = NULL;
	normal = NULL;
	if (hit->nearest->type == SPHERE)
	{
		rgb = obj->sp.rgb;
		normal = sphere_surface_normal(&obj->sp, hit->phit);
	}
	else if (hit->nearest->type == PLANE)
	{
		rgb = obj->pl.rgb;
		normal = plane_surface_normal(&obj->pl, ray);
	}
	else if (hit->nearest->type == CYLINDER)
		;
	
	// setup ambient
	ambient = rgb_multiply(rgb, space->ambient->rgb);
	// setup diffuse
	diffuse = vec3_init(0, 0, 0);
	// setup specular
	specular = vec3_init(0, 0, 0);

	// loop over each light
	c = 'x';
	i = 0;
	while (i < space->n_lights)
	{
		light = space->lights[i++];

		// build lray
		lray.origin = light->xyz;
		tmp = vec3_subtract(hit->phit, light->xyz);
		lray.direction = vec3_unit(tmp, 1);

		// find if lray hits object directly or not
		nearest_hit_object(&lray, space->objects, &lhit);
		if (lhit.nearest)
		{
			lobj = (t_object *)(lhit.nearest->content);
			if (lobj == obj)
			{
				// calculate lambertian reflectance - diffuse => https://en.wikipedia.org/wiki/Lambertian_reflectance
				// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/diffuse-lambertian-shading
				albedo = 0.18;
				
				tmp = vec3_multiply(light->rgb, light->brightness_ratio * vec3_dot(lray.direction, normal) * albedo / M_PI);
				vec3_add_to_self(&diffuse, tmp);
				free(tmp);

				if ((vec3_dot(lray.direction, normal) * albedo / M_PI) > 0.00001)
					c = 'o';

				// calculate specular reflectance
				// https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF/phong-illumination-models-brdf
				n = 250;

				tmp = vec3_multiply(normal, 2 * (vec3_dot(normal, lray.direction)));
				r = vec3_subtract(tmp, lray.direction);
				v = vec3_multiply(lray.direction, -1);
				tmp = vec3_multiply(light->rgb, light->brightness_ratio * pow(vec3_dot(v, r), n));
				vec3_add_to_self(&specular, tmp);
				vec3_free_multi(r, v, tmp);

				if ((pow(vec3_dot(v, ray->direction), n)) > 0.2)
					c = '*';
			}
		}
	}
	
	kd = 0.8;
	tmp = vec3_multiply(diffuse, kd);
	free(diffuse);
	diffuse = rgb_multiply(rgb, tmp);
	// diffuse = vec3_copy(tmp);
	free(tmp);

	ks = 0.15;
	tmp = vec3_multiply(specular, ks);
	free(specular);
	specular = vec3_copy(tmp);
	free(tmp);

	tmp = vec3_add(ambient, diffuse);
	hit->rgb = vec3_add(tmp, specular);
	free(tmp);
	vec3_free_multi(ambient, diffuse, specular);
	free(normal);
	return (c);
}

char	obj_to_char(t_obj_lst *elem)
{
	if (elem)
	{
		if (elem->type == LIGHT)
			return ('@');
		else if (elem->type == SPHERE)
			return ('o');
		else if (elem->type == PLANE)
			return ('-');
		else if (elem->type == CYLINDER)
			return ('%');
	}
	return ('.');
}

size_t	cast_ray(t_ray *ray, t_space *space, char *c)
{
	t_hit		hit;
	t_object	*obj;
	size_t		colour;

	nearest_hit_object(ray, space->objects, &hit);
	if (hit.nearest)
	{
		obj = (t_object *)(hit.nearest->content);
		if (hit.nearest->type == LIGHT)
			hit.rgb = vec3_copy(obj->l.rgb);
		else
		{
			hit.phit = ray_to_point(ray, hit.t);
			*c = shading(space, ray, &hit, obj);
			free(hit.phit);
		}
	}
	else
	{
		hit.rgb = vec3_copy(space->ambient->rgb);
		*c = '.';
	}
	// *c = obj_to_char(hit.nearest);
	colour = rgb_colour(hit.rgb);
	free(hit.rgb);
	return (colour);
}
