//Author Kyle Gian
//Date Created 2/4/2021
//Last Modified 6/4/2021

//Creates a camera instance based off information given for position, rotation and if it is stationary

#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 a_position, float a_xRotation, float a_yRotation, bool a_stationary);
	~Camera() {};

	void Update(float deltaTime);

	glm::vec3 GetPosition() { return m_position; }
	bool IsStationary() { return m_stationary; }


	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float a_width, float a_height);
private:
	float m_theta; //In degrees
	float m_phi; //In degrees
	glm::vec3 m_position;
	bool m_stationary;

	float m_lastMouseX, m_lastMouseY;
protected:
};

