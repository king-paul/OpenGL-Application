#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <iostream>
#include <glfw3.h>

using namespace glm;

const float MOVE_SPEED = 5;
const float TURN_SPEED = 0.1f;

class Camera
{
public:
	Camera(GLFWwindow* window, vec3 position);
	~Camera() { }
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix(float w, float h);

	void Update(float deltaTime);

	vec3 Forward() { return m_forward; }

private:

	// camera position and angle
	vec3 m_position;
	vec3 m_forward;
	float m_theta;
	float m_phi;
	float m_lastMouseX;
	float m_lastMouseY;

	GLFWwindow* m_window;
};