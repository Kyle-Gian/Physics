#pragma once
#include "RigidBody.h"

class Sphere : public RigidBody
{
public:
	Sphere(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_color);
	~Sphere() {};

	virtual void MakeGizmo();
	virtual bool IsInside(glm::vec2 a_point);

	float GetRadius() { return m_radius; }

	glm::vec4 GetColor() { return m_color; }

	void MakeVelocityZero(Sphere* a_sphere);

protected:
	float m_radius;
	glm::vec4 m_color;

};

