#include "Mesh.h"

Mesh::~Mesh() { 
	glDeleteVertexArrays(1, &vertexArray); 
	glDeleteBuffers(1, &vertexBuffer); 
	glDeleteBuffers(1, &indexBuffer); 
}

void Mesh::Initialise(unsigned int vertexCount, const Vertex* vertices, 
					  unsigned int indexCount, unsigned int* indices)
{
	assert(vertexArray == 0);

	// generate buffers
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArray);

	// bind vertex array aka a mesh wrapper 
	glBindVertexArray(vertexArray);

	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), 
		vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// bind indices if there are any
	if (indexCount != 0) {
		glGenBuffers(1, &indexBuffer);

		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		// fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int),
			indices, GL_STATIC_DRAW);

		triangleCount = indexCount / 3;
	}
	else { 
		triangleCount = vertexCount / 3; 
	}

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::InitialiseQuad() {

	// check that the mesh is not initialized already 
	assert(vertexArray == 0);

	// generate buffers 
	glGenBuffers(1, &vertexBuffer); 
	glGenVertexArrays(1, &vertexArray);

	// bind vertex array aka a mesh wrapper 
	glBindVertexArray(vertexArray); 

	// bind vertex buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// define 6 vertices for 2 triangles 
	Vertex vertices[6];
	// first triangle
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	// second triangle
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles 
	triangleCount = 2;
}

void Mesh::Draw() 
{
	//Shape3d::Draw();
	
	glBindVertexArray(vertexArray);
	// using indices or just vertices?

	shader->UseShader();

	if (indexBuffer != 0)
		glDrawElements(GL_TRIANGLES, 3 * triangleCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triangleCount);
}