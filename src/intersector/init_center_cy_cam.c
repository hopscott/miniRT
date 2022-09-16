/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center_cy_cam.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:19:27 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/16 15:22:25 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cy_params(t_cylinder *cylinder, t_camera *camera)
{
	cylinder->co = vec3_subtract(camera->xyz, cylinder->xyz);
	cylinder->cross_co_orient = vec3_cross(cylinder->co, cylinder->norm);
	cylinder->radius = cylinder->diameter / 2;
}

void	cy_init_cam_center(t_camera *camera, t_obj_lst **objs)
{
	t_obj_lst	*elem;
	t_obj_lst	*next;
	t_object	*obj;

	if (objs && *objs)
	{
		elem = *objs;
		while (elem)
		{
			next = elem->next;
			if (elem->content && elem->type == CYLINDER)
			{
				obj = (t_object *)(elem->content);
				init_cy_params(&(obj->cy), camera);
			}
			elem = next;
		}
	}
}
