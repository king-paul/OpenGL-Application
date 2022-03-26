#include "Shape3d.h"

Cube::Cube(Texture* texture) : Shape3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), texture)
{
	float cubeData[] = {

	// vertices //colour  // uv texture mapping
	0, 0, 1,   1, 0, 0,	  0, 0,
	0, 1, 1,   1, 0, 0,	  0, 1,
	1, 0, 1,   1, 0, 0,	  1, 0,
	0, 1, 1,   1, 0, 0,	  0, 1,
	1, 1, 1,   1, 0, 0,	  1, 1,
	1, 0, 1,   1, 0, 0,	  1, 0,

	0, 0, 0,   0, 0, 1,	  0, 0,
	0, 1, 0,   0, 0, 1,	  0, 1,
	1, 0, 0,   0, 0, 1,	  1, 0,
	0, 1, 0,   0, 0, 1,	  0, 1,
	1, 1, 0,   0, 0, 1,	  1, 1,
	1, 0, 0,   0, 0, 1,	  1, 0,

	0, 0, 0,   0, 1, 0,   0, 0,
	0, 0, 1,   0, 1, 0,	  0, 1,
	0, 1, 0,   0, 1, 0,	  1, 0,
	0, 0, 1,   0, 1, 0,	  0, 1,
	0, 1, 1,   0, 1, 0,	  1, 1,
	0, 1, 0,   0, 1, 0,	  1, 0,

	1, 0, 0,   0, 1, 1,   0, 0,
	1, 0, 1,   0, 1, 1,	  0, 1,
	1, 1, 0,   0, 1, 1,	  1, 0,
	1, 0, 1,   0, 1, 1,	  0, 1,
	1, 1, 1,   0, 1, 1,	  1, 1,
	1, 1, 0,   0, 1, 1,	  1, 0,

	0, 0, 0,   1, 1, 0,   0, 0,
	0, 0, 1,   1, 1, 0,	  0, 1,
	1, 0, 0,   1, 1, 0,	  1, 0,
	0, 0, 1,   1, 1, 0,	  0, 1,
	1, 0, 1,   1, 1, 0,	  1, 1,
	1, 0, 0,   1, 1, 0,	  1, 0,

	0, 1, 0,   1, 0, 1,   0, 0,
	0, 1, 1,   1, 0, 1,	  0, 1,
	1, 1, 0,   1, 0, 1,	  1, 0,
	0, 1, 1,   1, 0, 1,	  0, 1,
	1, 1, 1,   1, 0, 1,	  1, 1,
	1, 1, 0,   1, 0, 1,	  1, 0,

	};

	SetData(216, cubeData);
}

Cube::Cube(Texture* mainTexture, Texture* blendedTexture) :
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), mainTexture, blendedTexture)
{
	float cubeData[] = {

		// vertices //colour  // uv texture mapping
		0, 0, 1,   1, 0, 0,	  0, 0,
		0, 1, 1,   1, 0, 0,	  0, 1,
		1, 0, 1,   1, 0, 0,	  1, 0,
		0, 1, 1,   1, 0, 0,	  0, 1,
		1, 1, 1,   1, 0, 0,	  1, 1,
		1, 0, 1,   1, 0, 0,	  1, 0,

		0, 0, 0,   0, 0, 1,	  0, 0,
		0, 1, 0,   0, 0, 1,	  0, 1,
		1, 0, 0,   0, 0, 1,	  1, 0,
		0, 1, 0,   0, 0, 1,	  0, 1,
		1, 1, 0,   0, 0, 1,	  1, 1,
		1, 0, 0,   0, 0, 1,	  1, 0,

		0, 0, 0,   0, 1, 0,   0, 0,
		0, 0, 1,   0, 1, 0,	  0, 1,
		0, 1, 0,   0, 1, 0,	  1, 0,
		0, 0, 1,   0, 1, 0,	  0, 1,
		0, 1, 1,   0, 1, 0,	  1, 1,
		0, 1, 0,   0, 1, 0,	  1, 0,

		1, 0, 0,   0, 1, 1,   0, 0,
		1, 0, 1,   0, 1, 1,	  0, 1,
		1, 1, 0,   0, 1, 1,	  1, 0,
		1, 0, 1,   0, 1, 1,	  0, 1,
		1, 1, 1,   0, 1, 1,	  1, 1,
		1, 1, 0,   0, 1, 1,	  1, 0,

		0, 0, 0,   1, 1, 0,   0, 0,
		0, 0, 1,   1, 1, 0,	  0, 1,
		1, 0, 0,   1, 1, 0,	  1, 0,
		0, 0, 1,   1, 1, 0,	  0, 1,
		1, 0, 1,   1, 1, 0,	  1, 1,
		1, 0, 0,   1, 1, 0,	  1, 0,

		0, 1, 0,   1, 0, 1,   0, 0,
		0, 1, 1,   1, 0, 1,	  0, 1,
		1, 1, 0,   1, 0, 1,	  1, 0,
		0, 1, 1,   1, 0, 1,	  0, 1,
		1, 1, 1,   1, 0, 1,	  1, 1,
		1, 1, 0,   1, 0, 1,	  1, 0,

	};

	SetData(216, cubeData);
}

Cube::Cube(vec3 position, std::vector<vec3> colours) :
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"))
{
	vec3 indicies[] = {
		{ position.x + 0, position.y + 0, position.z + 0 }, // 0
		{ position.x + 0, position.y + 0, position.z + 1 }, // 1
		{ position.x + 0, position.y + 1, position.z + 0 }, // 2
		{ position.x + 0, position.y + 1, position.z + 1 }, // 3
		{ position.x + 1, position.y + 0, position.z + 0 }, // 4
		{ position.x + 1, position.y + 0, position.z + 1 }, // 5
		{ position.x + 1, position.y + 1, position.z + 0 }, // 6
		{ position.x + 1, position.y + 1, position.z + 1 }  // 7
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

	SetData(216, cubeData);
}

Cube::Cube(vec3 position, Texture* texture) : Shape3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), texture)
{
	vec3 indicies[] = {
		{ position.x + 0, position.y + 0, position.z + 0 }, // 0
		{ position.x + 0, position.y + 0, position.z + 1 }, // 1
		{ position.x + 0, position.y + 1, position.z + 0 }, // 2
		{ position.x + 0, position.y + 1, position.z + 1 }, // 3
		{ position.x + 1, position.y + 0, position.z + 0 }, // 4
		{ position.x + 1, position.y + 0, position.z + 1 }, // 5
		{ position.x + 1, position.y + 1, position.z + 0 }, // 6
		{ position.x + 1, position.y + 1, position.z + 1 }  // 7
	};

	vec3 uvs[]{{0, 0, 0}, {0, 1,0}, {1, 0, 0}, {0, 1,0}, {1, 1,0}, {1, 0, 0}};

	vec3 cubeData[] =
	{
		indicies[1], uvs[0], indicies[3], uvs[1], indicies[5], uvs[2],
		indicies[3], uvs[3], indicies[7], uvs[4], indicies[5], uvs[5],
		indicies[0], uvs[0], indicies[2], uvs[1], indicies[4], uvs[2],
		indicies[2], uvs[3], indicies[6], uvs[4], indicies[4], uvs[5],
		indicies[0], uvs[0], indicies[1], uvs[1], indicies[2], uvs[2],
		indicies[1], uvs[3], indicies[3], uvs[4], indicies[2], uvs[5],

		indicies[4], uvs[0], indicies[5], uvs[1], indicies[6], uvs[2],
		indicies[5], uvs[3], indicies[7], uvs[4], indicies[6], uvs[5],
		indicies[0], uvs[0], indicies[1], uvs[1], indicies[4], uvs[2],
		indicies[1], uvs[3], indicies[5], uvs[4], indicies[4], uvs[5],
		indicies[2], uvs[0], indicies[3], uvs[1], indicies[6], uvs[2],
		indicies[3], uvs[3], indicies[7], uvs[4], indicies[6], uvs[5],
	};

	/*
	// face 1
	polygons.push_back({ {indicies[1], uvs[0]}, {indicies[3], uvs[1]}, {indicies[5], uvs[2]} });
	polygons.push_back({ {indicies[3], uvs[3]}, {indicies[7], uvs[4]}, {indicies[5], uvs[5]} });
	// face 2
	polygons.push_back({ {indicies[0], uvs[0]}, {indicies[2], uvs[1]}, {indicies[4], uvs[2]} });
	polygons.push_back({ {indicies[2], uvs[3]}, {indicies[6], uvs[4]}, {indicies[4], uvs[5]} });
	// face 3
	polygons.push_back({ {indicies[0], uvs[0]}, {indicies[1], uvs[1]}, {indicies[2], uvs[2]} });
	polygons.push_back({ {indicies[1], uvs[3]}, {indicies[3], uvs[4]}, {indicies[2], uvs[5]} });
	// face 4
	polygons.push_back({ {indicies[4], uvs[0]}, {indicies[5], uvs[1]}, {indicies[6], uvs[2]} });	
	polygons.push_back({ {indicies[5], uvs[3]}, {indicies[7], uvs[4]}, {indicies[6], uvs[5]} });
	// face 5
	polygons.push_back({ {indicies[0], uvs[0]}, {indicies[1], uvs[1]}, {indicies[4], uvs[2]} });	
	polygons.push_back({ {indicies[1], uvs[3]}, {indicies[5], uvs[4]}, {indicies[4], uvs[5]} });
	// face 6
	polygons.push_back({ {indicies[2], uvs[0]}, {indicies[3], uvs[1]}, {indicies[6], uvs[2]} });
	polygons.push_back({ {indicies[3], uvs[3]}, {indicies[7], uvs[4]}, {indicies[6], uvs[5]} });
	*/

	SetData(228, cubeData);
}