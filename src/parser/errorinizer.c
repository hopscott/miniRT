/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorinizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 02:18:15 by omoudni           #+#    #+#             */
/*   Updated: 2022/08/15 02:44:30 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	putstr_error(char *err)
{
	write(2, err, ft_strlen(err));
}

void	print_help(void)
{
	write(2, HELP_MSG, ft_strlen(HELP_MSG));
}
