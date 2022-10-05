/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/20 16:30:29 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_lst	*obj_lstnew(int type, void *content)
{
	t_obj_lst	*elem;

	if (!content)
		return (NULL);
	elem = malloc(sizeof(t_obj_lst));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->content = content;
	elem->surface = CHECKERS;
	elem->next = NULL;
	return (elem);
}

t_obj_lst	*obj_lstlast(t_obj_lst *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	obj_lstadd(t_obj_lst **lst, int type, t_object *object)
{
	t_obj_lst	*new;
	t_obj_lst	*last;

	if (object == NULL)
		return (1);
	new = obj_lstnew(type, object);
	if (!new)
		return (1);
	if (lst && *lst)
	{
		last = obj_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
	return (0);
}

void	obj_lstfree(t_obj_lst **lst)
{
	t_obj_lst	*elem;
	t_obj_lst	*next;

	if (lst && *lst)
	{
		elem = *lst;
		while (elem)
		{
			next = elem->next;
			if (elem->content)
				free(elem->content);
			free(elem);
			elem = next;
		}
		lst = NULL;
	}
}
