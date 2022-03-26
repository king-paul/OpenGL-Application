#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix(float w, float h);
	void Update();

private:
	float theta;
	float phi;
	vec3 position;
	mat4 rotation;
	mat4 view;
	mat4 projection;
};