/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:44:48 by swillis           #+#    #+#             */
/*   Updated: 2022/10/10 13:47:18 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_matrix_with_transpose(double trans[4][4], t_mat44 *mat)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		mat->a[i] = trans[0][i];
		mat->b[i] = trans[1][i];
		mat->c[i] = trans[2][i];
		mat->d[i] = trans[3][i];
	}
}

void	transpose_matrix(t_mat44 *mat)
{
	int		i;
	int		j;
	double	cpy[4][4];
	double	trans[4][4];

	i = -1;
	while (++i < 4)
	{
		cpy[0][i] = mat->a[i];
		cpy[1][i] = mat->b[i];
		cpy[2][i] = mat->c[i];
		cpy[3][i] = mat->d[i];
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			trans[j][i] = cpy[i][j];
	}
	update_matrix_with_transpose(trans, mat);
}
