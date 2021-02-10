#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 a_position, glm::vec2 a_velocity, float a_mass, float a_radius, glm::vec4 a_color) : RigidBody(SPHERE, a_position, a_velocity, 0 , a_mass)
{
	m_radius = a_radius;
	m_color = a_color;
	m_moment = 0.5f * m_mass * m_radius * m_radius;

}

void Sphere::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_color);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1));
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
