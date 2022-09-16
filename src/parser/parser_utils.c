/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/14 17:04:32 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	init_parser_params(t_space *space)
{
	space->ambient = NULL;
	space->camera = NULL;
	space->cam = 0;
	space->amb = 0;
	space->objects = NULL;
	space->lights = NULL;
}
