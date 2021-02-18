#pragma once
#include "Application.h"
#include "Input.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include <vector>

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

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	PhysicsScene* m_physicsScene;

	const float m_aspectRatio = 16.f / 9.f;
	const float m_extents = 100;

public:
	void DrawRect();
	void SphereAndPlane();
	void DrawPool();
	void SpringTest(int a_amount);
	void TriggerTest();
	void AddBallToList(Sphere* a_ball);
	void AddPocketsToList(Sphere* a_pockets);

	void AddBallsToScene();
	void AddPocketsToScene();


	void AimAndShoot(aie::Input* a_input);
	bool CheckBallVelocity();

	void HasBallBeenSunk();
	void ResetBallPositions();

protected:
	std::vector<Sphere*> m_ballList;
	std::vector<Sphere*> m_pocketsList;
	std::vector<glm::vec2> m_ballStartPos;

	Sphere* m_cueBall = nullptr;
	Sphere* m_ball1 = nullptr;
	Sphere* m_ball2 = nullptr;
	Sphere* m_ball3 = nullptr;
	Sphere* m_ball4 = nullptr;
	Sphere* m_ball5 = nullptr;
	Sphere* m_ball6 = nullptr;
	Sphere* m_ball7 = nullptr;
	Sphere* m_ball8 = nullptr;
	Sphere* m_ball9 = nullptr;
	Sphere* m_ball10 = nullptr;
	Sphere* m_ball11 = nullptr;
	Sphere* m_ball12 = nullptr;
	Sphere* m_ball13 = nullptr;
	Sphere* m_ball14 = nullptr;
	Sphere* m_ball15 = nullptr;

	Sphere* m_topLeftPocket = nullptr;
	Sphere* m_botLeftPocket = nullptr;
	Sphere* m_topMidPocket = nullptr;
	Sphere* m_botMidPocket = nullptr;

	Sphere* m_topRightPocket = nullptr;
	Sphere* m_botRightPocket = nullptr;

	float m_ballPosOnceSunken = -75.f;
	bool m_shotTaken = false;
	bool m_ballSunkDuringTurn = false;
	bool m_ballVelocityZero = true;
};