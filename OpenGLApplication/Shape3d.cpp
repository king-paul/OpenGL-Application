#include "Shape3d.h"

Shape3d::Shape3d(ShaderProgram* shader)
{
	position = vec3(0, 0, 0);
	this->shader = shader;
	rotateAxis = vec3(0, 1, 0);

	transform = glm::identity<mat4>();
}

Shape3d::Shape3d(ShaderProgram* shader, Texture* texture)
{
	position = vec3(0, 0, 0);
	this->shader = shader;
	rotateAxis = vec3(0, 1, 0);

	transform = glm::identity<mat4>();

	this->texture = texture;
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

	// enables vertex attribures from vertex shaders
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	if (texture)
	{
		glEnableVertexAttribArray(2);
		texture->Bind();
	}
}

void Shape3d::Update(float deltaTime)
{
	// mat4 Rotate(mat4 matrix, float angle, vec3 axis);
	rotation = glm::rotate(glm::mat4(1), rotateSpeed * (float)glfwGetTime(), rotateAxis);
	//mat4 LookAt(vec3 cameraPosition, vec3 focalPoint, vec3 upDirection);
	view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// mat4 Perspective(float fovInRadians, float aspectRatio, float nearPlane, float farPlane);
	projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);

	shader->SetUniform("mvp", projection * view * rotation);	
}

void Shape3d::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	
	if (texture)
	{
		// assigns attributes from vertex shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Colour
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // UVs
	}
	else 
	{
		// assigns attributes from vertex shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Colour
	}

	shader->UseShader();

	glDrawArrays(GL_TRIANGLES, 0, 36); // draws the shape
}

void Shape3d::SetRotateMotion(vec3 axis, float speed)
{
	rotateAxis = axis;
	rotateSpeed = speed;
}