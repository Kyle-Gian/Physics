#include "RigidBody.h"
#include "PhysicsScene.h"
#include <iostream>

#define MIN_LINEAR_THRESHOLD 0.001f;
#define MIN_ANGULAR_THRESHOLD 0.001f;

RigidBody::RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
	m_rotation = a_rotation;
	m_angularVelocity = 0;
	m_elasticity = 0.8f;
	m_linearDrag = 0.8f;
	m_angularDrag = 1.f;
	m_isKinematic = false;
	m_isTrigger = false;
}

void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	//Checks if it is a trigger
	if (m_isTrigger)
	{
		//This will let us check every object that is inside this trigger
		//obbject and call triggerenter on of they haven't registered
		//inside the trigger this frame, they must have exited so we can remove
		// them from the lsit and then call triggerexit


		for (auto it = m_objectInside.begin(); it != m_objectInside.end(); it++)
		{
			if (std::find(m_objectInsideThisFrame.begin(), m_objectInsideThisFrame.end(), *it) == m_objectInsideThisFrame.end())
			{
				if (m_triggerExit)
				{
					m_triggerExit(*it);
				}
				it = m_objectInside.erase(it);
				if (it == m_objectInside.end())
				{
					break;
				}
			}
		}
	}

	//Clear the list now for the next frame
	m_objectInsideThisFrame.clear();

	if (m_isKinematic)
	{
		m_velocity = glm::vec2(0);
		m_angularVelocity = 0.f;
		return;
	}
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));

	//Slow object down over Time
	m_velocity -= m_velocity * m_linearDrag * a_timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * a_timeStep;

	if (glm::length(m_velocity) < 0.001f)
	{
		if (glm::length(m_velocity) < glm::length(a_gravity) * m_linearDrag * a_timeStep)
		{
			m_velocity = glm::vec2(0);
		}
	}
	if (abs(m_angularVelocity) < 0.001f)
	{
		m_angularVelocity = 0;
	}

	m_position += GetVelocity() * a_timeStep;

	m_rotation += m_angularVelocity * a_timeStep;
}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_pos)
{
	m_velocity += a_force / GetMass();
	m_angularVelocity += (a_force.y * a_pos.x + a_force.x * a_pos.y) / GetMoment();
}

void RigidBody::ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal, float a_pen)
{
	//Register that these two objects have overlapped this frame
	m_objectInsideThisFrame.push_back(a_otherActor);
	a_otherActor->m_objectInsideThisFrame.push_back(this);

	// Find the vector between their centers, or use the provided 
	// direction of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(a_collisionNormal ? *a_collisionNormal : a_otherActor->GetPosition() - GetPosition());

	//Get the vector perpendicular to the collision normal
	glm::vec2 perpendicularColNorm(normal.y, -normal.x);

	//These are applied to the radius from axis to the application of force
	float radius1 = glm::dot(a_contact - m_position, -perpendicularColNorm);
	float radius2 = glm::dot(a_contact - a_otherActor->GetPosition(), perpendicularColNorm);

	// Velocity of the contact point on this object
	float cp_velocity1 = glm::dot(m_velocity, normal) - radius1 * m_angularVelocity;

	//Velocity of contact point of the other object
	float cp_velocity2 = glm::dot(a_otherActor->m_velocity, normal) + radius2 * a_otherActor->m_angularVelocity;

	if (cp_velocity1 > cp_velocity2) // They are moving closer
	{
		//This will calculate the effective mass at the contact point of each
		// object ( How much it will move due to the forces applied)
		float mass1 = 1.f / (1.f / m_mass + (radius1 * radius1) / GetMoment());
		float mass2 = 1.f / (1.f / a_otherActor->m_mass + (radius2 * radius2) / a_otherActor->GetMoment());

		float elasticity = (m_elasticity + a_otherActor->GetElasticity() / 2);

		glm::vec2 impact = (1.f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (cp_velocity1 - cp_velocity2) * normal;
		if (!m_isTrigger && !a_otherActor->IsTrigger())
		{
			ApplyForce(-impact, a_contact - m_position);
			a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());

			if (m_collisionCallback != nullptr)
			{
				m_collisionCallback(a_otherActor);
			}

			if (a_otherActor->m_collisionCallback)
			{
				a_otherActor->m_collisionCallback(this);
			}
		}
		else
		{
			// Entered the Trigger
			TriggerEnter(a_otherActor);
			a_otherActor->TriggerEnter(this);
		}

		if (a_pen > 0)
		{
			PhysicsScene::ApplyContactForces(this, a_otherActor, normal, a_pen);
		}
	}
}

glm::vec2 RigidBody::ToWorld(glm::vec2 a_localPos)
{
	return m_position + m_localX * a_localPos.x + m_localY * a_localPos;
}

void RigidBody::TriggerEnter(PhysicsObject* a_otherActor)
{
	if (m_triggerEnter && std::find(m_objectInside.begin(),m_objectInside.end(), a_otherActor) == m_objectInside.end())
	{
		m_objectInside.push_back(a_otherActor);
		if (m_triggerEnter != nullptr)
		{
			m_triggerEnter(a_otherActor);
		}
	}
}
