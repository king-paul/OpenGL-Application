#pragma once
#include "glad.h"
#include <glm.hpp>
#include "Shape3d.h"

class Mesh : public Shape3d
{
public:

	Mesh() : Shape3d(new ShaderProgram("3dVertexShader.vsd", "3dFragmentShader.fsd")), 
		triangleCount(0), vertexArray(0), vertexBuffer(0), indexBuffer(0) { }
	Mesh(ShaderProgram* shader) : Shape3d(shader), triangleCount(0), vertexArray(0), vertexBuffer(0), indexBuffer(0) { }
	Mesh(unsigned int triCount, GLuint vao, GLuint vbo, GLuint ibo) : Shape3d(new ShaderProgram("3dVertexShader.vsd", "3dFragmentShader.fsd")), 
		triangleCount(triCount), vertexArray(vao), vertexBuffer(vbo), indexBuffer(ibo) { }
	~Mesh();

	struct Vertex { 
		glm::vec4 position; 
		glm::vec4 normal; 
		glm::vec2 texCoord; 
	};

	void Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, 
		unsigned int* indices = nullptr);
	void InitialiseQuad();
	void Draw() override;

protected:
	unsigned int triangleCount;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint indexBuffer;
};

