/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:33:02 by swillis           #+#    #+#             */
/*   Updated: 2022/09/14 16:51:28 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	space_render(t_data *data, int width, int height, t_space *space)
{
	t_param	param;
	t_ray	ray;

	ray.origin = space->camera->xyz;
	if (init_parameters(width, height, space, &param))
		return ;
	param.py = -1;
	while (++param.py < param.height)
	{
		param.px = -1;
		while (++param.px < param.width)
		{
			ray.direction = set_direction(param, param.matrix);
			if (ray.direction)
			{
				param.colour = cast_ray(&ray, space, \
					&param.screen_hit[(int)param.py][(int)param.px], \
					&param.screen_shading[(int)param.py][(int)param.px]);
				free(ray.direction);
			}
			my_mlx_pixel_put(data, param.px, param.py, param.colour);
		}
		print_progress(param.py, height);
	}
	print_screens_and_free_matrix(&param);
}
