/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_plan_bmap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:31:58 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/11 03:38:16 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	*normal_bmap_plane(t_plane *plane, t_hit *hit)
{
	t_vec3	*tmp;
	t_vec3	*normal;

	if ((int)((hit->phit->e[0] - plane->xyz->e[0]) / 10) % 2)
	{
		tmp = vec3_init(plane->norm->e[0] - abs((int)hit->phit->e[0] % 10), plane->norm->e[1], plane->norm->e[2]);
		normal = vec3_unit(tmp, 1);
	}
	else
	{
		tmp = vec3_init(plane->norm->e[0] + abs((int)hit->phit->e[0] % 10), plane->norm->e[1], plane->norm->e[2]);
		normal = vec3_unit(tmp, 1);
	}
	return (normal);
}
