#include "Shape3d.h"

Cube::Cube(std::vector<vec3> colours) :
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"))
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
	
	// face 1
	polygons.push_back({ Vertex(indicies[1], colours[0]), Vertex(indicies[3], colours[0]), Vertex(indicies[5], colours[0]) });
	polygons.push_back({ Vertex(indicies[3], colours[0]), Vertex(indicies[7], colours[0]), Vertex(indicies[5], colours[0]) });
	// face 2																	
	polygons.push_back({ Vertex(indicies[0], colours[1]), Vertex(indicies[2], colours[1]), Vertex(indicies[4], colours[1]) });
	polygons.push_back({ Vertex(indicies[2], colours[1]), Vertex(indicies[6], colours[1]), Vertex(indicies[4], colours[1]) });
	// face 3
	polygons.push_back({ Vertex(indicies[0], colours[2]), Vertex(indicies[1], colours[1]), Vertex(indicies[2], colours[2]) });
	polygons.push_back({ Vertex(indicies[1], colours[2]), Vertex(indicies[3], colours[2]), Vertex(indicies[2], colours[2]) });
	// face 4
	polygons.push_back({ Vertex(indicies[4], colours[3]), Vertex(indicies[5], colours[3]), Vertex(indicies[6], colours[3]) });
	polygons.push_back({ Vertex(indicies[5], colours[3]), Vertex(indicies[7], colours[3]), Vertex(indicies[6], colours[3]) });
	// face 5
	polygons.push_back({ Vertex(indicies[0], colours[4]), Vertex(indicies[1], colours[4]), Vertex(indicies[4], colours[4]) });
	polygons.push_back({ Vertex(indicies[1], colours[4]), Vertex(indicies[5], colours[4]), Vertex(indicies[4], colours[4]) });
	// face 6
	polygons.push_back({ Vertex(indicies[2], colours[5]), Vertex(indicies[3], colours[5]), Vertex(indicies[6], colours[5]) });
	polygons.push_back({ Vertex(indicies[3], colours[5]), Vertex(indicies[6], colours[5]), Vertex(indicies[6], colours[5]) });

	SetData(polygons.size() * sizeof(Polygon), (void*)polygons.data());
	
}

Cube::Cube(vec3 position, std::vector<vec3> colours) :
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"), position)
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

	// face 1
	polygons.push_back({ Vertex(indicies[1], colours[0]), Vertex(indicies[3], colours[1]), Vertex(indicies[5], colours[2]) });
	polygons.push_back({ Vertex(indicies[3], colours[3]), Vertex(indicies[7], colours[4]), Vertex(indicies[5], colours[5]) });
	// face 2																	
	polygons.push_back({ Vertex(indicies[0], colours[0]), Vertex(indicies[2], colours[1]), Vertex(indicies[4], colours[2]) });
	polygons.push_back({ Vertex(indicies[2], colours[3]), Vertex(indicies[6], colours[4]), Vertex(indicies[4], colours[5]) });
	// face 3
	polygons.push_back({ Vertex(indicies[0], colours[0]), Vertex(indicies[1], colours[1]), Vertex(indicies[2], colours[2]) });
	polygons.push_back({ Vertex(indicies[1], colours[3]), Vertex(indicies[3], colours[4]), Vertex(indicies[2], colours[5]) });
	// face 4
	polygons.push_back({ Vertex(indicies[4], colours[0]), Vertex(indicies[5], colours[1]), Vertex(indicies[6], colours[2]) });
	polygons.push_back({ Vertex(indicies[5], colours[3]), Vertex(indicies[7], colours[4]), Vertex(indicies[6], colours[5]) });
	// face 5
	polygons.push_back({ Vertex(indicies[0], colours[0]), Vertex(indicies[1], colours[1]), Vertex(indicies[4], colours[2]) });
	polygons.push_back({ Vertex(indicies[1], colours[3]), Vertex(indicies[5], colours[4]), Vertex(indicies[4], colours[5]) });
	// face 6
	polygons.push_back({ Vertex(indicies[2], colours[0]), Vertex(indicies[3], colours[1]), Vertex(indicies[6], colours[2]) });
	polygons.push_back({ Vertex(indicies[3], colours[3]), Vertex(indicies[7], colours[4]), Vertex(indicies[6], colours[5]) });

	SetData(polygons.size() * sizeof(Polygon), (void*)polygons.data());
	
}

Cube::Cube(vec3 position, Texture* main, Texture* blended) : 
	Shape3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), position, main, blended)
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

	vec2 uvs[]{ {0, 0}, {0, 1}, {1, 0}, {0, 1}, {1,0}, {1, 0} };
	
	// face 1
	polygons.push_back({ Vertex(indicies[1], uvs[0]), Vertex(indicies[3], uvs[1]), Vertex(indicies[5], uvs[2]) });
	polygons.push_back({ Vertex(indicies[3], uvs[3]), Vertex(indicies[7], uvs[4]), Vertex(indicies[5], uvs[5]) });
	// face 2																	
	polygons.push_back({ Vertex(indicies[0], uvs[0]), Vertex(indicies[2], uvs[1]), Vertex(indicies[4], uvs[2]) });
	polygons.push_back({ Vertex(indicies[2], uvs[3]), Vertex(indicies[6], uvs[4]), Vertex(indicies[4], uvs[5]) });
	// face 3
	polygons.push_back({ Vertex(indicies[0], uvs[0]), Vertex(indicies[1], uvs[1]), Vertex(indicies[2], uvs[2]) });
	polygons.push_back({ Vertex(indicies[1], uvs[3]), Vertex(indicies[3], uvs[4]), Vertex(indicies[2], uvs[5]) });
	// face 4
	polygons.push_back({ Vertex(indicies[4], uvs[0]), Vertex(indicies[5], uvs[1]), Vertex(indicies[6], uvs[2]) });
	polygons.push_back({ Vertex(indicies[5], uvs[3]), Vertex(indicies[7], uvs[4]), Vertex(indicies[6], uvs[5]) });
	// face 5
	polygons.push_back({ Vertex(indicies[0], uvs[0]), Vertex(indicies[1], uvs[1]), Vertex(indicies[4], uvs[2]) });
	polygons.push_back({ Vertex(indicies[1], uvs[3]), Vertex(indicies[5], uvs[4]), Vertex(indicies[4], uvs[5]) });
	// face 6
	polygons.push_back({ Vertex(indicies[2], uvs[0]), Vertex(indicies[3], uvs[1]), Vertex(indicies[6], uvs[2]) });
	polygons.push_back({ Vertex(indicies[3], uvs[3]), Vertex(indicies[7], uvs[4]), Vertex(indicies[6], uvs[5]) });

	SetData(polygons.size() * sizeof(Polygon), (void*)polygons.data());
	
}