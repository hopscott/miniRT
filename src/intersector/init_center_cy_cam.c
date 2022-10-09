/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_center_cy_cam.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:19:27 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/09 18:47:08 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cy_params(t_cylinder *cylinder, double xyz[3], int type)
{
	if (type == CAMERA)
	{
		vec_subtract(xyz, cylinder->xyz, &cylinder->co);
		vec_cross(cylinder->co, cylinder->norm, &cylinder->cross_co_orient);
		cylinder->radius = cylinder->diameter / 2;
	}
	if (type == LIGHT)
	{
		vec_subtract(xyz, cylinder->xyz, &cylinder->lo);
		vec_cross(cylinder->lo, cylinder->norm, &cylinder->cross_lo_orient);
	}
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
				init_cy_params(&(obj->cy), camera->xyz, CAMERA);
			}
			elem = next;
		}
	}
}
