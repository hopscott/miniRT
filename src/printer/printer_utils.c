/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/10/04 00:31:04 by swillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_columns(void)
{
	printf("\n");
	printf("     Type      ");
	printf("|");
	printf("         XYZ         ");
	printf("|");
	printf("       Normal        ");
	printf("|");
	printf("     RGB       ");
	printf("|");
	printf(" Diameter ");
	printf("|");
	printf(" Height ");
	printf("|");
	printf(" Brightness ");
	printf("|");
	printf(" FOV ");
	printf("\n");
	printf("---------------------------------------------------");
	printf("---------------------------------------------------");
	printf("------------\n");
}

void	print_ambient(t_ambient *amb)
{
	printf("##### AMBIENT  ");
	printf("|");
	printf("                     ");
	printf("|");
	printf("                     ");
	printf("|");
	printf(" (%3zu,%3zu,%3zu) ", amb->r, amb->g, amb->b);
	printf("|");
	printf("          ");
	printf("|");
	printf("        ");
	printf("|");
	printf("   %5.3f    ", amb->lighting_ratio);
	printf("|");
	printf("    ");
	printf("\n");
}

void	print_camera(t_camera *cam)
{
	printf("-<[0] CAMERA   ");
	printf("|");
	printf(" (%5.1lf,%5.1lf,%5.1lf) ", cam->x, cam->y, cam->z);
	printf("|");
	printf(" (%5.2f,%5.2f,%5.2f) ", cam->vec_x, cam->vec_y, cam->vec_z);
	printf("|");
	printf("               ");
	printf("|");
	printf("          ");
	printf("|");
	printf("        ");
	printf("|");
	printf("            ");
	printf("|");
	printf(" %3zu", cam->fov);
	printf("\n");
}

void	print_light(t_light *l)
{
	printf("((*)) LIGHT    ");
	printf("|");
	printf(" (%5.1lf,%5.1lf,%5.1lf) ", l->x, l->y, l->z);
	printf("|");
	printf("                     ");
	printf("|");
	printf(" (%3zu,%3zu,%3zu) ", l->r, l->g, l->b);
	printf("|");
	printf("          ");
	printf("|");
	printf("        ");
	printf("|");
	printf("   %5.3f    ", l->brightness_ratio);
	printf("|");
	printf("    ");
	printf("\n");
}
