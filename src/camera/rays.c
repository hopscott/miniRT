/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 20:17:24 by swillis           #+#    #+#             */
/*   Updated: 2022/09/07 23:02:05 by omoudni          ###   ########.fr       */
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
			cy_intersection(ray, &obj->cy, hit);
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

char	shading(t_space *space, t_ray *ray, t_hit *hit, t_object *obj)
{
	t_vec3		*rgb;
	t_vec3		*normal;
	t_vec3		*ambient;
	t_vec3		*diffuse;
	t_vec3		*specular;
	t_vec3		*tmp;
	t_ray		lray;
	t_hit		lhit;
	t_object	*lobj;
	t_light		*light;
	size_t		i;
	t_vec3 		*r;
	t_vec3 		*v;
	t_vec3 		*l;
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
//		normal = plane_surface_normal(&obj->pl, ray);
		normal = vec3_copy(obj->pl.norm);
		printf("final normal, x: %f, y: %f, z: %f\n", normal->e[0], normal->e[1], normal->e[2]);
	}
	else if (hit->nearest->type == CYLINDER)
	{
		rgb = obj->cy.rgb;
		normal = cylinder_surface_normal(&obj->cy, hit->phit);
	}
	// setup ambient
	ambient = vec3_multiply(space->ambient->rgb, space->ambient->lighting_ratio);
	// setup diffuse
	diffuse = vec3_init(0, 0, 0);
	kd = 0.8;
	// setup specular
	specular = vec3_init(0, 0, 0);
	ks = 0.15;

	// loop over each light
	c = '.';
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
				
				l = vec3_multiply(lray.direction, -1);
				if (vec3_dot(l, normal) > 0)
				{
					tmp = vec3_multiply(light->rgb, light->brightness_ratio * vec3_dot(l, normal));
					vec3_add_to_self(&diffuse, tmp);
					free(tmp);
				}
				free(l);

				// calculate specular reflectance
				// https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF/phong-illumination-models-brdf
				n = 20;

				tmp = vec3_multiply(normal, 2 * (vec3_dot(normal, lray.direction)));
				r = vec3_subtract(tmp, lray.direction);
				free(tmp);
				v = vec3_copy(ray->direction);
				if (pow(vec3_dot(v, r), n) > 0)
				{
					tmp = vec3_multiply(light->rgb, light->brightness_ratio * pow(vec3_dot(v, r), n));
					vec3_add_to_self(&specular, tmp);
					free(tmp);
				}

				if ((pow(vec3_dot(v, r), n)) * ks > kd * (vec3_dot(l, normal)))
					if ((pow(vec3_dot(v, r), n)) * ks > 0.001)
						c = '*';
				if (kd * (vec3_dot(l, normal)) > (pow(vec3_dot(v, r), n)) * ks)
					if (kd * (vec3_dot(l, normal)) > 0.001)
						c = 'o';
				vec3_free_multi(r, v, NULL);
			}
			else
				c = 'x';
		}
	}

	// https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF

	// obj->rgb * diffuse * kd
	tmp = vec3_multiply(diffuse, kd);
	free(diffuse);
	diffuse = vec3_copy(tmp);
	free(tmp);

	// specular * ks
	tmp = vec3_multiply(specular, ks);
	free(specular);
	specular = vec3_copy(tmp);
	free(tmp);

	// ambient + diffuse + specular
	tmp = vec3_add(ambient, diffuse);
	hit->rgb = vec3_add(tmp, specular);
	tmp = rgb_multiply(rgb, hit->rgb);
	free(hit->rgb);
	hit->rgb = vec3_copy(tmp);
	vec3_free_multi(diffuse, specular, tmp);
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
//		else if (hit.nearest->type == CYLINDER)
//			hit.rgb = vec3_copy(obj->cy.rgb);
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
