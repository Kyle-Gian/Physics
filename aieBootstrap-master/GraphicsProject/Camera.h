#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 a_position);
	~Camera() {};

	void Update(float deltaTime);

	glm::vec3 GetPosition() { return m_position; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float a_width, float a_height);
private:
	float m_theta; //In degrees
	float m_phi; //In degrees
	glm::vec3 m_position;

	float m_lastMouseX, m_lastMouseY;
protected:
};

