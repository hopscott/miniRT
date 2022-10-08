/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/08 15:33:42 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
