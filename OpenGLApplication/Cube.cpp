#include "Shape3d.h"

Cube::Cube() : Shape3d(new ShaderProgram("3dVertexShader.vsd", "3dFragmentShader.fsd"))
{
	float cubeData[] = {

	0, 0, 1,   1, 0, 0,
	0, 1, 1,   1, 0, 0,
	1, 0, 1,   1, 0, 0,
	0, 1, 1,   1, 0, 0,
	1, 1, 1,   1, 0, 0,
	1, 0, 1,   1, 0, 0,

	0, 0, 0,   0, 0, 1,
	0, 1, 0,   0, 0, 1,
	1, 0, 0,   0, 0, 1,
	0, 1, 0,   0, 0, 1,
	1, 1, 0,   0, 0, 1,
	1, 0, 0,   0, 0, 1,

	0, 0, 0,   0, 1, 0,
	0, 0, 1,   0, 1, 0,
	0, 1, 0,   0, 1, 0,
	0, 0, 1,   0, 1, 0,
	0, 1, 1,   0, 1, 0,
	0, 1, 0,   0, 1, 0,

	1, 0, 0,   0, 1, 1,
	1, 0, 1,   0, 1, 1,
	1, 1, 0,   0, 1, 1,
	1, 0, 1,   0, 1, 1,
	1, 1, 1,   0, 1, 1,
	1, 1, 0,   0, 1, 1,

	0, 0, 0,   1, 1, 0,
	0, 0, 1,   1, 1, 0,
	1, 0, 0,   1, 1, 0,
	0, 0, 1,   1, 1, 0,
	1, 0, 1,   1, 1, 0,
	1, 0, 0,   1, 1, 0,

	0, 1, 0,   1, 0, 1,
	0, 1, 1,   1, 0, 1,
	1, 1, 0,   1, 0, 1,
	0, 1, 1,   1, 0, 1,
	1, 1, 1,   1, 0, 1,
	1, 1, 0,   1, 0, 1,

	};

	SetData(cubeData);
}


Cube::Cube(vec3 position, std::vector<vec3> colours) :
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "3dFragmentShader.fsd"))
{
	vec3 indicies[] = {
		{ 0, 0, 0 }, // 0
		{ 0, 0, 1 }, // 1
		{ 0, 1, 0 }, // 2
		{ 0, 1, 1 }, // 3
		{ 1, 0, 0 }, // 4
		{ 1, 0, 1 }, // 5
		{ 1, 1, 0 }, // 6
		{ 1, 1, 1 }  // 7
	};

	vec3 cubeData[] =
	{
		indicies[1], colours[0], indicies[3], colours[0], indicies[5], colours[0],
		indicies[3], colours[0], indicies[7], colours[0], indicies[5], colours[0],
		indicies[0], colours[1], indicies[2], colours[1], indicies[4], colours[1],
		indicies[2], colours[1], indicies[6], colours[1], indicies[4], colours[1],
		indicies[0], colours[2], indicies[1], colours[2], indicies[2], colours[2],
		indicies[1], colours[2], indicies[3], colours[2], indicies[2], colours[2],
		indicies[4], colours[3], indicies[5], colours[3], indicies[6], colours[3],
		indicies[5], colours[3], indicies[7], colours[3], indicies[6], colours[3],
		indicies[0], colours[4], indicies[1], colours[4], indicies[4], colours[4],
		indicies[1], colours[4], indicies[5], colours[4], indicies[4], colours[4],
		indicies[2], colours[5], indicies[3], colours[5], indicies[6], colours[5],
		indicies[3], colours[5], indicies[7], colours[5], indicies[6], colours[5],
	};

	SetData(cubeData);
}