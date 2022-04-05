#include "Shape3d.h"

Shape3d::Shape3d(ShaderProgram* shader, vec3 position, Texture* main, Texture* blend) :
	shader(shader), position(position), mainTexture(main), blendedTexture(blend)
	//Object3d(shader, position, main, blend)
{
	rotateAxis = vec3(0, 1, 0);
	transform = glm::identity<mat4>();
}

Shape3d::Shape3d(ShaderProgram* shader, vec3 position, Texture* diffuse, Texture* normal, Texture* specular):
	shader(shader), position(position), diffuse(diffuse), normal(normal), specular(specular)
	//Object3d(shader, position, diffuse, normal, specular)
{
	rotateAxis = vec3(0, 1, 0);
	transform = glm::identity<mat4>();
}

Shape3d::~Shape3d()
{
	delete shader;
}

void Shape3d::SetData(unsigned int bufferSize, const void* data)
{	
	glGenBuffers(1, &vertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// enables vertex attribures from vertex shaders
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	if (mainTexture)
	{
		glEnableVertexAttribArray(2);
		mainTexture->Bind(0);

		if (blendedTexture)
			blendedTexture->Bind(1);		
	}
	else if (diffuse && normal)// && specular)
	{
		glEnableVertexAttribArray(2);
		diffuse->Bind(0);
		normal->Bind(1);
		//specular->Bind(2);
	}
	
}


void Shape3d::Update(float deltaTime)
{
	// mat4 Rotate(mat4 matrix, float angle, vec3 axis);
	rotation = glm::rotate(glm::mat4(1), rotateSpeed * (float)glfwGetTime(), rotateAxis);
	//mat4 LookAt(vec3 cameraPosition, vec3 focalPoint, vec3 upDirection);
	view = glm::lookAt(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// mat4 Perspective(float fovInRadians, float aspectRatio, float nearPlane, float farPlane);
	projection = glm::perspective(PI / 4, 1920.0f / 1080, 0.1f, 100.0f);

	// set projection and view
	shader->SetUniform("mvpMatrix", projection * view * rotation);
	shader->SetUniform("modelMatrix", rotation);

	if (mainTexture)
	{
		shader->SetUniform("baseTexture", 0);

		if(blendedTexture)
			shader->SetUniform("blendedTexture", 1);
	}
	else if (diffuse && normal)
	{
		shader->SetUniform("diffuseTexture", 0);
		shader->SetUniform("normalMap", 1);
	}

	shader->SetUniform("fromLight", -glm::normalize(glm::vec3(1, -1, 1)));
}

void Shape3d::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	
	if (mainTexture)
	{
		// assigns attributes from vertex shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))); // Colour
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float))); // UVs
	}
	else 
	{
		// assigns attributes from vertex shader
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))); // Colour
	}

	shader->UseShader();

	glDrawArrays(GL_TRIANGLES, 0, polygons.size() * 3); // draws the shape
}

// Translate, rotate and scale
void Shape3d::SetPosition(float x, float y, float z)
{
	glm::translate(transform, vec3(x, y, z));
}

void Shape3d::SetRotation(vec3 axis, float angle)
{
	glm::rotate(transform, angle, axis);
}

void Shape3d::SetScale(float x, float y, float z)
{
	glm::scale(transform, vec3(x, y, z));
}