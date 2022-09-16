/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_er.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:39:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/16 21:18:06 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera(t_camera **camera)
{
	if (camera && (*camera) && (*camera)->xyz)
		free((*camera)->xyz);
	if (camera && (*camera) && (*camera)->norm)
		free((*camera)->norm);
}

void	free_ambient(t_ambient **amb_ptr)
{
	t_ambient	*ambient;

	ambient = *amb_ptr;
	if (ambient && ambient->rgb)
		free(ambient->rgb);
}

void	free_lights(t_light ***lights_ptr, size_t n_lights)
{
	t_light		**lights;
	size_t		i;

	lights = *lights_ptr;
	i = 0;
	while (i < n_lights)
	{
		free(lights[i]);
		i++;
	}
	free(lights);
}

void	free_space(t_space *space)
{
	if (space)
	{
		if (space->camera)
			free_camera(&(space->camera));
		if (space->ambient)
			free_ambient(&(space->ambient));
		if (space->objects)
			obj_lstfree(&(space->objects));
		if (space->lights)
			free(space->lights);
		if (space->arb_vecs)
			vec3_free_multi(space->arb_vecs->v1, space->arb_vecs->v2, space->arb_vecs->v3, 0);
	}
}
