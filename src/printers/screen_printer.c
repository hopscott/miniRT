/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:12:26 by swillis           #+#    #+#             */
/*   Updated: 2022/10/08 15:29:53 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_screen(char **screen)
{
	int	y;	
	int	x;

	printf("    ");
	x = -1;
	while (++x < WIDTH + 2)
		if (x % 10 == 0)
			printf("_");
	printf("_\n");
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		if (y % 20 == 0)
			printf("%4d|", y);
		while (++x < WIDTH)
			if ((x % 10 == 0) && (y % 20 == 0))
				printf("%c", screen[y][x]);
		if (y % 20 == 0)
			printf("|\n");
	}
}
