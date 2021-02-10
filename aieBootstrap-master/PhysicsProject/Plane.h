#pragma once
#include "PhysicsObject.h"


// This is a one-sided object that extends onfinitely along both it's
// edge and backwards from it's normal direction
class RigidBody;

class Plane :
	public PhysicsObject
{
public :
	Plane(glm::vec2 a_normal, float a_distance);
	Plane();
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Draw() {};
	virtual void Debug() {};
	virtual void ResetPosition() {};
	virtual void MakeGizmo();

	void ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact);

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColor() { return m_color; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_color;
};

