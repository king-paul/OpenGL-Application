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

Object3d::Object3d(ShaderProgram* shader, vec3 position, Texture* diffuse, Texture* normal, Texture* specular, float specularPower) :
	shader(shader), texDiffuse(diffuse), texNormal(normal), texSpecular(specular), specularPower(specularPower)
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

void Object3d::Update(float deltaTime, Camera* camera, std::vector<Light>& lights)
{
	// mat4 Rotate(mat4 matrix, float angle, vec3 axis);
	if(rotateAxis != vec3(0, 0, 0))
		transform = glm::rotate(glm::mat4(1), rotateSpeed * (float)glfwGetTime(), rotateAxis);

	view = camera->GetViewMatrix();	
	projection = camera->GetProjectionMatrix(1920, 1080);

	// set projection and view
	shader->SetUniform("mvpMatrix", projection * view * transform);
	shader->SetUniform("modelMatrix", transform);

	if (texDiffuse)
	{
		shader->SetUniform("diffuseMap", 0);

		if(texNormal)
			shader->SetUniform("normalMap", 1);

		if (texSpecular)
		{
			shader->SetUniform("specularMap", 2);
			shader->SetUniform("cameraForward", camera->Forward());
			shader->SetUniform("specularPower", specularPower);
		}
	}

	// Add lighting to shaders
	shader->SetUniform("fromLight1", -glm::normalize(lights[0].m_direction));
	shader->SetUniform("fromLight2", -glm::normalize(lights[1].m_direction));
	shader->SetUniform("light1Multiplier", lights[0].m_intensity);
	shader->SetUniform("light2Multiplier", lights[1].m_intensity);
	shader->SetUniform("lightColour1", lights[0].m_colour);
	shader->SetUniform("lightColour2", lights[1].m_colour);

	//shader->SetUniform("lights", lights);
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