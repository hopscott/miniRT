/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:28:56 by swillis           #+#    #+#             */
/*   Updated: 2022/09/17 15:37:36 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	space_free(t_space *space)
{
	t_camera	*cam;
	t_ambient	*amb;

	cam = space->camera;
	amb = space->ambient;
	obj_lstfree(&space->objects);
	vec3_free_multi(cam->xyz, cam->norm, amb->rgb, 0);
	free(space->lights);
}

int	main(int ac, char **av)
{
	char		*path;
	t_space		space;
	t_camera	camera;
	t_ambient	ambient;
	t_arb_vecs	arb_vecs;

	if (ac != 2)
		return (puterr_free(ERROR_ARGS, NULL), 1);
	else if (ac == 2 && !ft_strncmp(av[1], "--help", 7))
		return (print_help(), 0);
	path = av[1];
	if (init_3_arb_vec3(&space, &arb_vecs))
		return (puterr_free(FATAL_ERROR, &space), 1);
	if (parser(path, &space, &camera, &ambient))
		return (puterr_free(ERROR_PARSING, &space), 1);
	print_space(&space);
	mlx_render(&space);
	if (space.fatal_error)
		puterr_free(FATAL_ERROR, NULL);
	free_space(&space);
	return (0);
}


//TOOLS TO PRINT SHIT
/*

t_vec3 *pl = vec3_init(0, 1, 0);
	t_vec3 *cross = vec3_unit(vec3_cross(pl, space.arb_vecs->v1), 1);
	t_vec3 *cross2 = vec3_unit(vec3_cross(pl, cross), 0);
	printf(" %f %f %f\n", cross->e[0],  cross->e[1], cross->e[2]);
	printf(" %f %f %f\n", cross2->e[0],  cross2->e[1], cross2->e[2]);
	printf("-------------------");
	printf("arb_v1: %f %f %f\n", space.arb_vecs->v1->e[0],  space.arb_vecs->v1->e[1], space.arb_vecs->v1->e[2]);
	printf("arb_v2: %f %f %f\n", space.arb_vecs->v2->e[0],  space.arb_vecs->v2->e[1], space.arb_vecs->v2->e[2]);
	printf("arb_v3: %f %f %f\n", space.arb_vecs->v3->e[0],  space.arb_vecs->v3->e[1], space.arb_vecs->v3->e[2]);



	if (space.objects)
	{
		int	i;
		i = 0;
		t_obj_lst	*elem;
		t_object	*obj;
		elem = space.objects;
		while(elem)
		{
			if (elem->type == PLANE)
			{
				obj = (t_object *)elem->content;
				printf("i: %d e1.x: %f e1.y: %f e1.z: %f\n",i, obj->pl.e1->e[0], obj->pl.e1->e[1],obj->pl.e1->e[2]);
				printf("i: %d e2.x: %f e2.y: %f e2.z: %f\n",i,  obj->pl.e2->e[0], obj->pl.e2->e[1],obj->pl.e2->e[2]);
				i++;
			}
			elem = elem->next;
		}
	}
	exit(0);
*/
