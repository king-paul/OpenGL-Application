#include "Camera.h"

Camera::Camera(GLFWwindow* window, vec3 position) : m_position(position), m_window(window)
{

}

mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

mat4 Camera::GetProjectionMatrix(float w, float h)
{
	return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.f);
}

//----------------------------//
// Camera movement from input //
//----------------------------//
void Camera::Update(float deltaTime)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	//calculate the forwards and right axes and up axis for the camera
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	// use WASD, ZX keys to move camera around
	
	// forward, back, left and right
	if (glfwGetKey(m_window, GLFW_KEY_W) || glfwGetKey(m_window, GLFW_KEY_UP))
		m_position += forward * MOVE_SPEED * deltaTime;
	if (glfwGetKey(m_window, GLFW_KEY_S) || glfwGetKey(m_window, GLFW_KEY_DOWN))
		m_position -= forward * MOVE_SPEED * deltaTime;
	if (glfwGetKey(m_window, GLFW_KEY_A) || glfwGetKey(m_window, GLFW_KEY_LEFT))
		m_position -= right * MOVE_SPEED * deltaTime;
	if (glfwGetKey(m_window, GLFW_KEY_D) || glfwGetKey(m_window, GLFW_KEY_RIGHT))
		m_position += right * MOVE_SPEED * deltaTime;

	// up and down
	if (glfwGetKey(m_window, GLFW_KEY_Z))
		m_position += up * MOVE_SPEED * deltaTime;
	if (glfwGetKey(m_window, GLFW_KEY_X))
		m_position -= up * MOVE_SPEED * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_P))
		std::cout << "Camera Position (" << m_position.x << ", " << m_position.y << ", " 
										 << m_position.z << ")" << std::endl;

	// get the current mouse coordinates
	double mouseX, mouseY;
	glfwGetCursorPos(m_window, &mouseX, &mouseY);
	
	// if the right button is down, increment theta and phi
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		//std::cout << "Cursor is at position (" << mouseX << ", " << mouseY << ")" << std::endl;

		m_theta += TURN_SPEED * (mouseX - m_lastMouseX);
		m_phi -= TURN_SPEED * (mouseY - m_lastMouseY);
	}

	// store this frames values for next frame
	m_lastMouseX = mouseX;
	m_lastMouseY = mouseY;
}