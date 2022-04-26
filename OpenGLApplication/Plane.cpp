#include "Shape3d.h"

Plane::Plane(vec3 position, float scaleX , float scaleY, vec3 colour) 
	: Object3d(new ShaderProgram("3dVertexShader.vsd", "ColourShader.fsd"))
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

Plane::Plane(vec3 position, float scaleX, float scaleY, Texture* texture, Texture* normal, Texture* specular)
	: Object3d(new ShaderProgram("3dVertexShader.vsd", "TextureShader.fsd"), position, texture, normal, specular)
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

	polygons.push_back({ { vertices[0], {0, 0} }, { vertices[1], {0, 1} }, { vertices[2], {1, 0} } });
	polygons.push_back({ { vertices[3], {0, 1} }, { vertices[4], {1, 1} }, { vertices[5], {1, 0} } });

	SetData(sizeof(Vertex) * polygons.size(), (void*)polygons.data());
}

void Plane::Update(float deltaTime)
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

	if (texDiffuse)
	{
		shader->SetUniform("diffuseTexture", 0);

		if (texNormal)
			shader->SetUniform("normalMap", 1);
	}

	shader->SetUniform("fromLight", -glm::normalize(glm::vec3(1, -1, 1)));
}

void Plane::Draw()
{
	CheckOpenGLError();
	//if (!texDiffuse)
		//glDisableVertexAttribArray(2);

	//glDisableVertexAttribArray(3);
	//glDisableVertexAttribArray(4);
	//glDisableVertexAttribArray(5);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	if (texDiffuse)
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

	CheckOpenGLError();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Plane::SetData(unsigned int bufferSize, const void* data)
{
	glGenBuffers(1, &vertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// enables vertex attribures from vertex shaders
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	if (texDiffuse)
	{
		glEnableVertexAttribArray(2);
		texDiffuse->Bind(0);

		if (texNormal)
			texNormal->Bind(1);
	}
}