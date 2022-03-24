#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.inl>

using namespace glm;

class Camera
{
public:
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix(float w, float h);

private:
	float theta;
	float phi;
	vec3 position;
};