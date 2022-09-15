/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/15 17:02:06 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_space_null(t_space *space)
{
	if (!space->ambient && !space->camera && !space->objects && !space->lights)
		return (1);
	if (!space->camera && !space->ambient)
		return (2);
	return (0);
}

int	line_is_space(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (i == len)
		return (1);
	return (0);
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

void	init_parser_params(t_space *space)
{
	space->ambient = NULL;
	space->camera = NULL;
	space->cam = 0;
	space->amb = 0;
	space->objects = NULL;
	space->lights = NULL;
	space->fatal_error = 0;
}

int	dptr_len(char **tbl)
{
	int	len;

	len = 0;
	while (tbl && tbl[len])
		len++;
	return (len);
}


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
