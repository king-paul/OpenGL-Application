#include "Object3d.h"
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>

Object3d::Object3d(ShaderProgram* shader, vec3 position, vec3 colour) :
	shader(shader), colour(colour)
{
	transform = glm::identity<mat4>();
	transform[3].x = position.x;
	transform[3].y = position.y;
	transform[3].z = position.z;

}

Object3d::Object3d(ShaderProgram* shader, vec3 position, Texture* diffuse, Texture* normal, Texture* specular) :
	shader(shader), texDiffuse(diffuse), texNormal(normal), texSpecular(specular)
{
	transform = glm::identity<mat4>();
	transform[3].x = position.x;
	transform[3].y = position.y;
	transform[3].z = position.z;
}

Object3d::~Object3d()
{
	delete shader;
}

void Object3d::Update(float deltaTime, Camera* camera)
{
	// mat4 Rotate(mat4 matrix, float angle, vec3 axis);
	transform = glm::rotate(glm::mat4(1), rotateSpeed * (float)glfwGetTime(), rotateAxis);
	//mat4 LookAt(vec3 cameraPosition, vec3 focalPoint, vec3 upDirection);
	view = camera->GetViewMatrix(); //glm::lookAt(glm::vec3(5, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// mat4 Perspective(float fovInRadians, float aspectRatio, float nearPlane, float farPlane);
	projection = camera->GetProjectionMatrix(1920, 1080); //glm::perspective(PI / 4, 1920.0f / 1080, 0.1f, 100.0f);

	// set projection and view
	shader->SetUniform("mvpMatrix", projection * view * transform);
	shader->SetUniform("modelMatrix", transform);

	if (texDiffuse)
	{
		shader->SetUniform("diffuse", 0);

		if(texNormal)
			shader->SetUniform("normal", 0);

		if(texSpecular)
			shader->SetUniform("specular", 1);
	}

	shader->SetUniform("fromLight", -glm::normalize(glm::vec4(1, -1, 1, 0)));
}

// Translate, rotate and scale
void Object3d::SetPosition(float x, float y, float z)
{
	glm::translate(transform, vec3(x, y, z));
}

void Object3d::SetRotation(vec3 axis, float angle)
{
	glm::rotate(transform, angle, axis);
}

void Object3d::SetScale(float x, float y, float z)
{
	glm::scale(transform, vec3(x, y, z));
}

void Object3d::SetRotateMotion(vec3 axis, float speed)
{
	rotateAxis = axis;
	rotateSpeed = speed;
}