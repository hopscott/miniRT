/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:59:53 by omoudni           #+#    #+#             */
/*   Updated: 2022/09/18 15:57:03 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sub_get_uv(t_vec3 *tmp, t_vec3 *norm, t_vec3 **e1)
{
	*e1 = vec3_unit(vec3_cross(norm, tmp), 1);
	if (!*e1)
		return (-1);
	if (check_vec3_null(*e1))
		return (free(*e1), 1);
	return (0);
}

int	init_3_arb_vec3(t_space *space, t_arb_vecs *arb_vecs)
{
	t_vec3	*v1;
	t_vec3	*v2;
	t_vec3	*v3;

	v1 = vec3_init(1,0,0);
	if (!v1)
		return (1);
	v2 = vec3_init(0,1,0);
	if (!v2)
		return (free(v1), 1);
	v3 = vec3_init(0,0,1);
	if (!v3)
	{
		free(v1);
		free(v2);
		return (1);
	}
	arb_vecs->v1 = v1;
	arb_vecs->v2 = v2;
	arb_vecs->v3 = v3;
	space->arb_vecs = arb_vecs;
	return (0);
}

int	get_e1(t_space *space, t_plane *plane)
{
	int		ret;

	ret = sub_get_uv(space->arb_vecs->v1, plane->norm, &plane->e1);
	if (ret == -1)
		return (1);
	else if (ret == 1)
	{
		printf("I entered here 1\n");
		ret = sub_get_uv(space->arb_vecs->v2, plane->norm, &plane->e1);
		if (ret == -1)
			return (1);
		else if (ret == 1)
		{
			printf("I entered here 2\n");
			ret = sub_get_uv(space->arb_vecs->v3, plane->norm, &plane->e1);
			if (ret)
				return (1);
		}
	}
	return (0);
}

int	get_e2(t_plane *plane)
{
	plane->e1 = vec3_unit(plane->e1, 1);
	if (!plane->e1)
		return (1);
	plane->e2 = vec3_unit(vec3_cross(plane->norm, plane->e1), 1);
	if (!plane->e2)
		return (1);
	return (0);
}

int	get_e1_e2(t_space *space, t_plane *plane)
{
	if (get_e1(space, plane))
		return (1);
	if (get_e2(plane))
		return (1);
	return (0);
}
