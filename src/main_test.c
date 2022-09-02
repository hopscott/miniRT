#include "minirt.h"

int	main()
{
	t_vec3	*r_or;
	t_vec3	*dir;
	t_cylinder	cy;
	double		dist;

	r_or = vec3_init(3, 0, 0);
	dir = vec3_init(-1, 1, 0);
	cy.x = 0;
	cy.y = 0;
	cy.z = 0;
	cy.diameter = 2;
	cy.height = 5;
	cy.vec_x = 0;
	cy.vec_y = 1;
	cy.vec_z = 0;
	dist = cy_intersection(r_or, dir, &cy);
	printf("dist: %f\n", dist);
	return (0);
}
