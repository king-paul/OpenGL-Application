#include "Shape2d.h"

Shape2d::Shape2d(vec4 colour, ShaderProgram* shader)
{
	this->shader = shader;
	shader->SetUniform("aspectRatio", 16.0f / 9.0);
	shader->SetUniform("red", colour.r);
	shader->SetUniform("green", colour.g);
	shader->SetUniform("blue", colour.b);
	shader->SetUniform("alpha", colour.a);
}

void Shape2d::SetData(GLsizeiptr size, const void* data)
{
	glGenBuffers(1, &id);

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
}

void Shape2d::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	shader->UseShader();	
}

void Shape2d::Update(float deltaTime)
{
	if (clockwiseRotation)
		rotation -= rotationSpeed * deltaTime;
	else
		rotation += rotationSpeed * deltaTime;

	if (rotation >= 6.283 || rotation <= - 6.283)
		rotation = 0;

	shader->SetUniform("rotation", rotation);
}

void Shape2d::SetRotateMotion(float speed, bool clockwise)
{
	rotationSpeed = speed;
	clockwiseRotation = clockwise;
}

Triangle::Triangle(vec2 p1, vec2 p2, vec2 p3, vec4 colour) 
	: Shape2d(colour, new ShaderProgram("TriangleShader.vsd", "SimpleShader2d.fsd"))
{
	float data[] = { p1.x, p1.y, p2.x, p2.y, p3.x, p3.y };
	SetData(6, data);
}

void Triangle::Draw()
{
	Shape2d::Draw();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Rectangle::Rectangle(vec2 center, float width, float height, vec4 colour)
	: Shape2d(colour, new ShaderProgram("SquareShader.vsd", "SimpleShader2d.fsd"))
{
	vec2 p1 = { center.x - width / 2, center.y + height / 2 };
	vec2 p2 = { center.x + width / 2, center.y + height / 2 };
	vec2 p3 = { center.x + width / 2, center.y - height / 2 };
	vec2 p4 = { center.x - width / 2, center.y - height / 2 };

	float data[] = { p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y };
	SetData(8, data);
}

void Rectangle::Draw()
{
	Shape2d::Draw();
	glDrawArrays(GL_QUADS, 0, 4);
}