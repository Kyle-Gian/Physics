#pragma once
#include <glm/glm.hpp>
#include<vector>

#include "RigidBody.h"
class PhysicsObject;

class PhysicsScene
{

public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	//this will call the update of each PhysicsObjects and updates
	//internally. This will handle object collision and resolution
	void Update(float dt);

	//called once per frame and handles the rendering of PhysicsObjects
	//will add to a loop of gizmo objects to render
	void Draw();
	void DebugScene();

	void SetGravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float GetTimeStep() const { return m_timeStep; }

	void CheckForCollision();
	static void ApplyContactForces(RigidBody* a_actor1, RigidBody* a_actor2, glm::vec2 a_collisionNorm, float a_pen);

	static bool Plane2Plane(PhysicsObject*, PhysicsObject*);
	static bool Plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Plane2Box(PhysicsObject*, PhysicsObject*);

	static bool Sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Box(PhysicsObject*, PhysicsObject*);

	static bool Box2Box(PhysicsObject*, PhysicsObject*);
	static bool Box2Plane(PhysicsObject*, PhysicsObject*);
	static bool Box2Sphere(PhysicsObject*, PhysicsObject*);



protected:
	glm::vec2 m_gravity;
	float m_timeStep;

	std::vector<PhysicsObject*> m_actors;
};

