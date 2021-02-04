#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_color) : RigidBody(SPHERE, a_position, a_velocity, 0 , a_mass)
{
	m_radius = a_radius;
	m_color = a_color;
}

void Sphere::MakeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
}

bool Sphere::CheckCollision(PhysicsObject* pOther)
{
	Sphere* pShere = dynamic_cast<Sphere*>(pOther);

	if (pShere != nullptr)
	{
		float dist = glm::distance(m_position, pShere->GetPosition());

		if (GetRadius() + pShere->GetRadius() > dist)
		{
			return true;
		}
	}

	return false;
}
