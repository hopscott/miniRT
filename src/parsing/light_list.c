/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/17 21:48:45 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light_lst	*light_lstnew(t_light *light)
{
	t_light_lst	*elem;

	if (!light)
		return (NULL);
	elem = malloc(sizeof(t_light_lst));
	if (!elem)
		return (NULL);
	elem->light = light;
	elem->next = NULL;
	return (elem);
}

t_light_lst	*light_lstlast(t_light_lst *elem)
{
	if (!elem)
		return (NULL);
	while (elem->next)
		elem = elem->next;
	return (elem);
}

int	light_lstadd(t_light_lst **lights, t_light *light)
{
	t_light_lst	*new;
	t_light_lst	*last;

	if (light == NULL)
		return (1);
	new = light_lstnew(light);
	if (!new)
		return (1);
	if (lights && *lights)
	{
		last = light_lstlast(*lights);
		last->next = new;
	}
	else
		*lights = new;
	return (0);
}

void	light_lstfree(t_light_lst **lst)
{
	t_light_lst	*elem;
	t_light_lst	*next;

	if (lst && *lst)
	{
		elem = *lst;
		while (elem)
		{
			next = elem->next;
			if (elem->light)
				free(elem->light);
			free(elem);
			elem = next;
		}
		lst = NULL;
	}
}
