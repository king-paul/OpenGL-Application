#include "Camera.h"
#include <ext/matrix_clip_space.hpp>

mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(theta);
	float phiR = glm::radians(phi);
	vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	return glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

mat4 Camera::GetProjectionMatrix(float w, float h)
{
	return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.f);
}

void Camera:: Update()
{

}