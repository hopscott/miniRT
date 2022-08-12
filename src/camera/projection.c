/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:51:44 by swillis           #+#    #+#             */
/*   Updated: 2022/08/12 18:59:22 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt"

void	object_space_to_camera_space(t_list **lst)
{
	t_list		*elem;
	t_object	*obj;

	elem = *lst;
	while (elem)
	{
		obj = (t_object *)(elem->content);
		if (elem->type == AMBIENT)
			continue ;
		else if (elem->type == CAMERA)
			continue ;
		else if (elem->type == LIGHT)
			continue ;
		else if (elem->type == SPHERE)
			continue ;
		else if (elem->type == PLANE)
			continue ;
		else if (elem->type == CYLINDER)
			continue ;
		elem = elem->next;
	}
}
