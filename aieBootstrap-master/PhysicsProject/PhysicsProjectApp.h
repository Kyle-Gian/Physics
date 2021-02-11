#pragma once
#include "Application.h"
#include "Input.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"

class PhysicsProjectApp : public aie::Application {
public:

	PhysicsProjectApp();
	virtual ~PhysicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	const float m_aspectRatio = 16.f / 9.f;
	const float m_extents = 100;

public:
	void DrawRect();
	void SphereAndPlane();
	void DrawPool();
	void SpringTest(int a_amount);
	void TriggerTest();
	void AimAndShoot(aie::Input* a_input);

protected:

	Sphere* m_cueBall;
	Sphere* m_ball1;
	Sphere* m_ball2;
	Sphere* m_ball3;
	Sphere* m_ball4;
	Sphere* m_ball5;
	Sphere* m_ball6;
	Sphere* m_ball7;
	Sphere* m_ball8;
	Sphere* m_ball9;
	Sphere* m_ball10;
	Sphere* m_ball11;
	Sphere* m_ball12;
	Sphere* m_ball13;
	Sphere* m_ball14;
	Sphere* m_ball15;
};