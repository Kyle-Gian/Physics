#pragma once
#include "PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_rotation);

	~RigidBody() {};

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug() {};
	void ApplyForce(glm::vec2 a_force);
	void ApplyforceToOther(RigidBody* a_otherActor, glm::vec2 a_force);

	void ResolveCollision(RigidBody* a_otherActor);

	virtual bool CheckCollision(PhysicsObject* pOther) = 0;



	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetMass() { return m_mass; }
	float GetRotation() { return m_rotation; }



protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;

	float m_mass;
	float m_rotation;
};

