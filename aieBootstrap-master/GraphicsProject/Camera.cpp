#include "Camera.h"
#include <glm/ext.hpp>
#include <Input.h>

Camera::Camera()
{
	m_position = glm::vec3(-10, 2, 0);
	m_phi = 0;
	m_theta = 0;
}

Camera::Camera(glm::vec3 a_position)
{
	m_position = a_position;
	m_phi = 0;
	m_theta = 0;
}

void Camera::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));
	
	glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
	glm::vec3 up(0, 1, 0);


#pragma region InputMovement

	if (input->isKeyDown(aie::INPUT_KEY_X))
	{
		m_position += up * 5.f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_Z))
	{
		m_position -= up * 5.f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{

		m_position -= right * 5.f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		m_position += right * 5.f * deltaTime;
	}	
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		m_position += forward * 5.f * deltaTime;
	}	
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		m_position -= forward * 5.f * deltaTime;
	}

#pragma endregion
	//Get the current position of the mouse coordinates
	float mx = input->getMouseX();
	float my = input->getMouseY();
	
	const float turnSpeed = glm::radians(180.f);

	//If the right button is down, increment the theta and phi
	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += turnSpeed * (mx - m_lastMouseX) * deltaTime;
		m_phi += turnSpeed * (my - m_lastMouseY) * deltaTime;
	}

	//Now store the frames last values for the next
	m_lastMouseX = mx;
	m_lastMouseY = my;

}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(glm::cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));

	return glm::lookAt(m_position, m_position + forward, glm::vec3(0,1,0));
}

glm::mat4 Camera::GetProjectionMatrix(float a_width, float a_height)
{
	return glm::perspective(glm::pi<float>() * 0.25f, a_width / a_height, 0.1f, 1000.f);
}
