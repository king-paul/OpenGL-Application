#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include "ShaderProgram.h"

using namespace glm;

class Camera
{
public:

	Camera(int width, int height);
	~Camera() { delete shader; }
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix(float w, float h);
	void Update(float deltaTime);

private:	
	
	mat4 rotation;
	mat4 view;
	mat4 projection;

	int windowWidth, windowHeight;

	ShaderProgram* shader;

	// camera position and angle
	vec3 m_position;
	float m_theta;
	float m_phi;
	float m_lastMouseX;
	float m_lastMouseY;
};