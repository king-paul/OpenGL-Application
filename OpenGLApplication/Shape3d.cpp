#include "Shape3d.h"

Shape3d::Shape3d(ShaderProgram* shader)
{
	position = vec3(0, 0, 0);
	this->shader = shader;
}

Shape3d::~Shape3d()
{
	delete shader;
}

void Shape3d::SetData(const void* data)
{
	glGenBuffers(1, &triangleID);

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 216, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Shape3d::Update(float deltaTime)
{
	rotation = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));
	view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);

	shader->SetUniform("mvp", projection * view * rotation);
}

void Shape3d::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	shader->UseShader();

	glDrawArrays(GL_TRIANGLES, 0, 36); // draws the shape
}

// Cube //
Cube::Cube() : Shape3d(new ShaderProgram("3dVertexShader.vsd", "3dFragmentShader.fsd"))
{
	float aBunchOfFloats[] = {

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

	SetData(aBunchOfFloats);
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

	/*
	float r1 = colours[0].r;
	float g1 = colours[0].g;
	float b1 = colours[0].b;
	float r2 = colours[1].r;
	float g2 = colours[1].g;
	float b2 = colours[1].b;
	float r3 = colours[2].r;
	float g3 = colours[2].g;
	float b3 = colours[2].b;
	float r4 = colours[3].r;
	float g4 = colours[3].g;
	float b4 = colours[3].b;
	float r5 = colours[4].r;
	float g5 = colours[4].g;
	float b5 = colours[4].b;
	float r6 = colours[5].r;
	float g6 = colours[5].g;
	float b6 = colours[5].b;*/

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