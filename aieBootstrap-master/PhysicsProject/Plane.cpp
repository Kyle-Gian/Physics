#include "Plane.h"
#include <Gizmos.h>

Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distance;
	m_color = glm::vec4(0, 1, 0, 1);
}

Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0, 1);
	m_distanceToOrigin = 0;
	m_color = glm::vec4(1, 1, 1, 1);
}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
}

void Plane::MakeGizmo()
{
	float lineSegmentLength = 300.f;
	glm::vec2 centerPoint = GetNormal() * m_distanceToOrigin;

	glm::vec2 parralel(GetNormal().y, -GetNormal().x);
	glm::vec4 colorFade = m_color;
	colorFade.a = 0;
	glm::vec2 start = centerPoint + (parralel * lineSegmentLength);

	glm::vec2 end = centerPoint - (parralel * lineSegmentLength);

	aie::Gizmos::add2DTri(start, end, start - GetNormal() * 10.f, GetColor(), GetColor(), colorFade);
	aie::Gizmos::add2DTri(end, end - GetNormal() * 10.f, start - GetNormal() * 10.f, GetColor(), colorFade, colorFade);
}
