/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/16 16:44:43 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fatal_error_int(t_space *space)
{
	space->fatal_error = 1;
	return (0);
}

void	fatal_error(t_space *space)
{
	space->fatal_error = 1;
}

void	free_params(t_param *param)
{
	tbl_free(&param->screen_shading);
	tbl_free(&param->screen_hit);
	free(param->matrix);
}

void	print_screens_and_free_matrix(t_param *param)
{
	print_screen(param->screen_hit);
	print_screen(param->screen_shading);
	tbl_free(&param->screen_shading);
	tbl_free(&param->screen_hit);
	free(param->matrix);
}
