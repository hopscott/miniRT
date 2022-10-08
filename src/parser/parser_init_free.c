/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/08 15:34:39 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_parser_params(t_space *space)
{
	vec_set(1, 0, 0, &space->arb_vecs.v1);
	vec_set(0, 1, 0, &space->arb_vecs.v2);
	vec_set(0, 0, 1, &space->arb_vecs.v3);
	space->ambient = NULL;
	space->camera = NULL;
	space->cam = 0;
	space->amb = 0;
	space->objects = NULL;
	space->lights = NULL;
	space->fatal_error = 0;
}

void	pl_cy_tbl_free(t_cylinder **cy, t_plane **p, char ***tbl)
{
	int		len;
	int		i;
	char	**tmp;

	tmp = *tbl;
	if (tmp)
	{
		len = dptr_len(tmp);
		i = -1;
		while (++i < len)
			free(tmp[i]);
		free(tmp);
	}
	if (cy && *cy)
		free(*cy);
	if (p && *p)
		free(*p);
}

void	tbl_free(char ***tbl)
{
	int		len;
	int		i;
	char	**tmp;

	tmp = *tbl;
	if (tmp)
	{
		len = dptr_len(tmp);
		i = -1;
		while (++i < len)
			free(tmp[i]);
		free(tmp);
	}
}

int	dptr_len(char **tbl)
{
	int	len;

	len = 0;
	while (tbl && tbl[len])
		len++;
	return (len);
}
