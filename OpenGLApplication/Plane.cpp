#include "Shape3d.h"

PlaneOld::PlaneOld(vec3 position, float scaleX , float scaleY, vec3 colour)
	: Shape3d(new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"))
{
	vec3 vertices[] = {	
						// first triangle
						vec3(position.x + (- 1 * scaleX) ,position.y, position.z + (1 * scaleY)),
					    vec3(position.x + (1 * scaleX), position.y, position.z + (1 * scaleY)),
						vec3(position.x + (- 1 * scaleX), position.y, position.z + (-1 * scaleY)),

						// second triangle
						vec3(position.x + (-1 * scaleX), position.y, position.z + (-1 * scaleY)),
						vec3(position.x + (1 * scaleX), position.y, position.z + (1 * scaleY)),
						vec3(position.x + (1 * scaleX), position.y, position.z + (-1 * scaleY))
	};
	
	//std::vector<PlainPolygon> triangles;
	polygons.push_back({ Vertex(vertices[0], colour), Vertex(vertices[1], colour), Vertex(vertices[2], colour) });
	polygons.push_back({ Vertex(vertices[3], colour), Vertex(vertices[4], colour), Vertex(vertices[5], colour) });

	SetData(sizeof(Polygon) * polygons.size(), (void*)polygons.data());
}

PlaneOld::PlaneOld(Texture* texture, vec3 position, float scaleX, float scaleY)
	: Shape3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), position, texture)
{	
	vec3 vertices[] = {	// first triangle
						vec3(position.x + (- 1 * scaleX) ,position.y, position.z + (1 * scaleY)),
						vec3(position.x + (1 * scaleX), position.y, position.z + (1 * scaleY)),
						vec3(position.x + (- 1 * scaleX), position.y, position.z + (-1 * scaleY)),

						// second triangle
						vec3(position.x + (-1 * scaleX), position.y, position.z + (-1 * scaleY)),
						vec3(position.x + (1 * scaleX), position.y, position.z + (1 * scaleY)),
						vec3(position.x + (1 * scaleX), position.y, position.z + (-1 * scaleY))
	};

	//polygons.push_back({ { vertices[0], {0, 0} }, { vertices[1], {0, 1} }, { vertices[2], {1, 0} } });
	//polygons.push_back({ { vertices[3], {0, 1} }, { vertices[4], {1, 1} }, { vertices[5], {1, 0} } });

	SetData(sizeof(Vertex) * polygons.size(), (void*)polygons.data());
}