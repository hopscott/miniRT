/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:49:25 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/19 10:45:56 by swillis          ###   ########.fr       */
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
