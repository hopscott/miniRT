# miniRT

**miniRT** is a project from the **42** Common Core, The project aims to build your own raytracer from scratch in C.


## Usage

	~/shell$> make
	~/shell$> ./miniRT example.rt
	
To use CUSTOM texture maps (must be in .xpm format)
	
	~/shell$> ./miniRT example.rt example_texture.xpm
	
To use CUSTOM texture maps + bump maps (must be in .xpm format)
	
	~/shell$> ./miniRT example.rt example_texture.xpm example_bump.xpm

## .rt file Scene General Components

### Ambient

	Id: A
	Ratio in range [0.0, 1.0]
	Color in RGB format in range [0-255] introduced as R,G,B


### Camera

	Id: C
	Coordinates (floats) introduced as x,y,z 
	3d orientation vector in [-1,1] range as V_x,V_y,V_z 
	FOV in [0, 180] range

### Light spots (1 light spot per line)

	Id: L
	Coordinates (floats) introduced as x,y,z
	Brightness ratio in range [0.0, 0.1]
	Color in RGB format in range [0-255] introduced as R,G,B

### Planes

	Id: pl
	Center's coordinates (floats) introduced as x,y,z
	3d orientation vector in [-1,1] range as V_x,V_y,V_z 
	Color in RGB format in range [0-255] introduced as R,G,B

### Spheres

	Id: sp
	Center's coordinates introduced as x,y,z 
	Diameter (float)
	Color in RGB format in range [0-255] introduced as R,G,B

### Cylinders

	Id: cy
	Base's center' coordinates introduced as x,y,z 
	3d orientation vector in [-1,1] range as V_x,V_y,V_z 
	Diameter (float)
	Height (float)
	Color in RGB format in range [0-255] introduced as R,G,B

## Layout of .rt file

	Ambient
	A	ratio	R,G,B

	Camera
	C	x,y,z	V_x,V_y,V_z

	Light spots
	L	x,y,z	Brightness_ratio	R,G,B

	Sphere
	sp	x,y,z	diameter	R,G,B

	Plane
	pl	x,y,z	V_x,V_y,V_z

	Cylinder
	cy	x,y,z	V_x,V_y,V_z	diameter	height	R,G,B

Check the example.rt file
