/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/06 23:30:20 by swillis          ###   ########.fr       */
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

int	check_space_null(t_space *space)
{
	if (!space->ambient && !space->camera && !space->objects && !space->lights)
		return (1);
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

int	surface_parser(char **tbl)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	while (tbl[i + 2])
		i++;
	s1 = tbl[i];
	s2 = tbl[i + 1];
	if (!ft_strncmp(s1, "CHECKERS", 8) || !ft_strncmp(s1, "checkers", 8))
		return (CHECKERS);
	else if (!ft_strncmp(s2, "CHECKERS", 8) || !ft_strncmp(s2, "checkers", 8))
		return (CHECKERS);
	else if (!ft_strncmp(s1, "TEXTURE", 7) || !ft_strncmp(s1, "texture", 7))
		return (TEXTURE);
	else if (!ft_strncmp(s1, "BUMP", 4) || !ft_strncmp(s1, "bump", 4))
		return (BUMP);
	else if (!ft_strncmp(s1, "BUMPTEXT", 8) || !ft_strncmp(s1, "bumptext", 8))
		return (BUMPTEXT);
	return (NONE);
}

int	material_parser(char **tbl)
{
	int		i;
	char	*str;

	i = 0;
	while (tbl[i + 1])
		i++;
	str = tbl[i];
	if (!ft_strncmp(str, "BRICK", 5) || !ft_strncmp(str, "brick", 5))
		return (BRICK);
	else if (!ft_strncmp(str, "WOOD", 4) || !ft_strncmp(str, "wood", 4))
		return (WOOD);
	else if (!ft_strncmp(str, "CUSTOM", 6) || !ft_strncmp(str, "custom", 6))
		return (CUSTOM);
	return (ERROR);
}
