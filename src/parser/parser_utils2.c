/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/16 16:48:58 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	tbl_3_check(char **tbl)
{
	int	len;

	len = dptr_len(tbl);
	if (len != 3)
		return (1);
	return (0);
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

int	check_rt(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 3)
		return (1);
	if (ft_strncmp(&(path[len - 3]), ".rt", 3))
		return (1);
	return (0);
}
