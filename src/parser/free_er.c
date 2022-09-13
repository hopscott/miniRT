/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_er.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:39:52 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/13 02:39:47 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera(t_camera **cam_ptr)
{
	t_camera	*camera;

	camera = *cam_ptr;
	if (camera->xyz)
		free(camera->xyz);
	if (camera->norm)
		free(camera->norm);
	free(camera);
}

void	free_ambient(t_ambient **amb_ptr)
{
	printf("I entered here!\n");
	t_ambient	*ambient;

	ambient = *amb_ptr;
	if (ambient->rgb)
		free(ambient->rgb);
	free(ambient);
}

void	free_lights(t_light ***lights_ptr, size_t n_lights)
{
	t_light	**lights;
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
	printf("I entered here2!\n");
	if (space)
	{
		if (space->camera)
			free_camera(&(space->camera));
		if (space->ambient)
			free_ambient(&(space->ambient));
		if (space->objects)
			obj_lstfree(&(space->objects));
		if (space->lights)
			free_lights(&(space->lights), space->n_lights);
		//space = NULL;
	}
}
