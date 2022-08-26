#include <math.h>
#include <stdio.h>

typedef struct	s_vec3 {
	double	x;
	double	y;
}				t_vec3;

typedef struct	s_cercle {
	double	radius;
	t_vec3	center;
}				t_cercle;

void	find_ab(double (*ab)[2], t_vec3 orig, t_vec3 dir)
{
	double	a;
	double	b;

	a = dir.y / dir.x;
	b = orig.y - a * orig.x;
	(*ab)[0] = a;
	(*ab)[1] = b;
}

void	find_quadratic_coef(double (*cde)[3], double ab[2], t_cercle cercle)
{
	double	a;
	double	b;
	double	xc;
	double	yc;
	double	rc;
	double	c;
	double	d;
	double	e;

	a = ab[0];
	b = ab[1];
	xc = cercle.center.x;
	yc = cercle.center.y;
	rc = cercle.radius;
	c = 1 + pow(a, 2);
	d = 2 * a * b - 2 * xc - 2 * a * yc;
	e = pow(xc,2) + pow(yc, 2) - pow(rc, 2) + pow(b, 2) - 2 * b * yc;
	(*cde)[0] = c;
	(*cde)[1] = d;
	(*cde)[2] = e;
}

int	check_det(double *det1, double a, double b, double c)
{
	float	det;

	det = sqrt(pow(b, 2) - 4 * a *c);
	printf("det: %f\n", det);
	*det1 = det;
	if (det < 0)
		return (0);
	if (det == 0)
		return (1);
	else
		return (2);
}

void	get_xs(double (*x1x2)[2], double det, double a, double b, double c)
{

	(*x1x2)[0] = (-b + det) / (2 * a);
	printf("x1: %f\n", (*x1x2)[0]);
	(*x1x2)[1] = (-b - det) / (2 * a);
	printf("x2: %f\n", (*x1x2)[1]);
}

double	get_x(double a, double b, double c)
{
	return (-b / (2 * a));
}

double	dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	find_dis_1(double x1x2[2], t_vec3 orig, double ab[2])
{
	double	y1;
	double	y2;
	double	dist1;
	double	dist2;
	double	a = ab[0];
	double	b = ab[1];

	y1 = a * x1x2[0] + b;
	printf("y1: %f\n", y1);
	y2 = a * x1x2[1] + b;
	printf("y2: %f\n", y2);
	dist1 = dist(orig.x, orig.y, x1x2[0], y1);
	printf("dist1: %f\n", dist1);
	dist2 = dist(orig.x, orig.y, x1x2[1], y2);
	printf("dist2: %f\n", dist2);
	if (dist1 < dist2)
		return (dist1);
	else
		return (dist2);
}

double	find_dis_2(double x, t_vec3 orig, double ab[2])
{
	double	y;
	double	a = ab[0];
	double	b = ab[1];

	y = a * x + b;
	return (dist(orig.x, orig.y, x, y));
}

double	dist_line_cer(t_vec3 orig, t_vec3 dir, t_cercle cercle)
{
	double	ab[2];
	double	cde[3];
	double	abc[3];
	double	a;
	double	b;
	double	c;
	int		num_sol;
	double	x1x2[2];
	double	x;
	double	det;

	det = 0;
	find_ab(&ab, orig, dir);
	printf("a: %f\n", ab[0]);
	printf("b: %f\n", ab[1]);
	find_quadratic_coef(&cde, ab, cercle);
	printf("c: %f\n", cde[0]);
	printf("d: %f\n", cde[1]);
	printf("e: %f\n", cde[2]);
	a = cde[0];
	b = cde[1];
//	b = -4;
	c = cde[2];
	x = 0;
	num_sol = check_det(&det, a, b, c);
	printf("num_sol: %d\n", num_sol);
	if (num_sol == 2)
	{
		get_xs(&x1x2, det, a, b, c);
		return (find_dis_1(x1x2, orig, ab));
	}
	else if (num_sol == 1)
	{
		x = get_x(a, b, c);
		return (find_dis_2(x, orig, ab));
	}
	return (-1);
}


int	main(int argc, char **argv)
{
	t_vec3		orig;
	t_vec3		dir;
	t_cercle	cercle;
	double		dist;

	orig.x = -3;
	orig.y = 6;
	dir.x = 1;
	dir.y = -1;
	cercle.radius = 4;
	cercle.center.x = -1;
	cercle.center.y = 0;
	dist = dist_line_cer(orig, dir, cercle);
	printf("dist should be 2: %f\n", dist);
	return (0);
}
