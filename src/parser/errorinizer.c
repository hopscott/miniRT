/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorinizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:18:15 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/14 21:34:58 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	puterr_free(char *err, t_space *space)
{
	write(2, err, ft_strlen(err));
	if (space)
		free_space(space);
}

void	print_help(void)
{
	write(2, HELP_MSG, ft_strlen(HELP_MSG));
}
