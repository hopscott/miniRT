/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swillis <swillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:46:19 by swillis           #+#    #+#             */
/*   Updated: 2022/09/26 16:19:49 by jpalma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* https://www.scratchapixel.com/lessons/					 */
/* mathematics-physics-for-computer-graphics/lookat-function */

#include <stdlib.h>
#include <stdio.h>

typedef struct s_mat44 {
double	a[4];
double	b[4];
double	c[4];
double	d[4];
}		t_mat44;

t_mat44	*mat44_init(double a[3], double b[3], double c[3], double d[3])
{
	t_mat44	*mat;
	int		i;

	mat = malloc(sizeof(t_mat44));
	if (!mat)
		return (NULL);
	i = -1;
	while (++i < 3)
		mat->a[i] = a[i];
	mat->a[i] = 0;
	i = -1;
	while (++i < 3)
		mat->b[i] = b[i];
	mat->b[i] = 0;
	i = -1;
	while (++i < 3)
		mat->c[i] = c[i];
	mat->c[i] = 0;
	i = -1;
	while (++i < 3)
		mat->d[i] = d[i];
	mat->d[i] = 1;
	return (mat);
}

/* https://math.stackexchange.com/questions/89621/how-to-multiply-vector- */
/* 3-with-4by4-matrix-more-precisely-position-transformat 				  */
void	mat_x_mat_utils(double (*col_to_fill)[3], t_mat44 *mat1, double col[3], int d)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (d) 
			(*col_to_fill)[i] = mat1->a[i] *  col[0] + mat1->b[i] * col[1] + mat1->c[i] * col[2] + mat1->d[i];
		else
			(*col_to_fill)[i] = mat1->a[i] *  col[0] + mat1->b[i] * col[1] + mat1->c[i] * col[2];
		i++;
	}
}

t_mat44	*mat_x_mat(t_mat44 *mat1, t_mat44 *mat2, int to_free)
{
	double	a[3];
	double	b[3];
	double	c[3];
	double	d[3];
	t_mat44	*ret;
	
	mat_x_mat_utils(&a, mat1, mat2->a, 0);
	mat_x_mat_utils(&b, mat1, mat2->b, 0);
	mat_x_mat_utils(&c, mat1, mat2->c, 0);
	mat_x_mat_utils(&d, mat1, mat2->d, 1);
	if (to_free)
	{
		free(mat1);
		free(mat2);
	}
	ret = mat44_init(a, b, c, d);
	return (ret);
}

t_mat44	*set_rx(double angle)
{
double	a[3];
double	b[3];
double	c[3];
double	d[3];
t_mat44	*r_x;

a[0] = 1;
a[1] = 21;
a[2] = 12;
b[0] = 0;
b[1] = 570;
b[2] = -10;
c[0] = 0.7;
c[1] = -30.6;
c[2] = 70;
d[0] = 100;
d[1] = 0.5;
d[2] = 10;
r_x = mat44_init(a, b, c, d);
return (r_x);
}

t_mat44	*set_ry(double angle)
{
double	a[3];
double	b[3];
double	c[3];
double	d[3];
t_mat44	*r_y;

a[0] = 1010; 
a[1] = 0.5;
a[2] = 30;
b[0] = 35;
b[1] = 400;
b[2] = 1;
c[0] = 2;
c[1] = 3.6;
c[2] = 4;
d[0] = 50;
d[1] = 2;
d[2] = 10;
r_y = mat44_init(a, b, c, d);
return (r_y);
}


void	print_mat(t_mat44 *mat)
{
	printf("%f %f %f %f\n", mat->a[0], mat->b[0], mat->c[0], mat->d[0]);
	printf("%f %f %f %f\n", mat->a[1], mat->b[1], mat->c[1], mat->d[1]);
	printf("%f %f %f %f\n", mat->a[2], mat->b[2], mat->c[2], mat->d[2]);
	printf("0 0 0 1\n");
}

int	main(int argc, char **argv)
{
	t_mat44	*r_x;
	t_mat44	*r_y;

	r_x = set_rx(5);
	r_y = set_ry(5);
	print_mat(mat_x_mat(r_x, r_y, 1));
	return (0);
}
