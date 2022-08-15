/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/08/15 02:25:58 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list	*ft_lstnew(int type, void *content)
{
	t_list	*elem;

	if (!content)
		return (NULL);
	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->type = type;
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && *lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	free_lst_tbl(t_list **lst, char **tbl)
{
	t_list	*tmp;

	ft_freetbl(tbl, -1);
	if (lst)
	{
		if (*lst)
		{
			while (*lst)
			{
				tmp = *lst;
				*lst = (*lst)->next;
				free (tmp);
			}
		}
		free(lst);
		lst = NULL;
	}
}
