/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_uv_cy_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:04:04 by omoudni           #+#    #+#             */
/*   Updated: 2022/10/06 16:07:16 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_new_norm(double old_norm[3], double (*new_norm)[3])
{
	(*new_norm)[0] = -1 * old_norm[0];
	(*new_norm)[1] = old_norm[1];
	(*new_norm)[2] = -1 * old_norm[2];
}
