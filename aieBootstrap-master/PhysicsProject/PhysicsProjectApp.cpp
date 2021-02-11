#include "PhysicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"

PhysicsProjectApp::PhysicsProjectApp() {

}

PhysicsProjectApp::~PhysicsProjectApp() {

}

bool PhysicsProjectApp::startup() {
	//increases the 2D line count to maximise the number of objects we can draw
	aie::Gizmos::create(225U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, 0));

	//lower the value, the more accurate the simulation will be;
	// but it will increase the processing time required. If it 
	// is too high it cause the sim to stutter and reduce stability
	m_physicsScene->SetTimeStep(0.01f);

	//DrawRect();

	DrawPool();

	//SpringTest(10);
	//TriggerTest();

	//SphereAndPlane();
	return true;
}

void PhysicsProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	if (input->isMouseButtonDown(0))
	{
		int xScreen, yScreen;
		input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.3));
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsProjectApp::draw() {
	// wipe the screen to the background colour
	clearScreen();


	// X-axis = -100 to 100, y-axis = -56.25 to 56.25
	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents, -m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.f, 1.f));

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

glm::vec2 PhysicsProjectApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;

	//We will move the center of the screen to 0,0
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	//Scale this according to the extents
	worldPos.x *= 2.f * m_extents / getWindowWidth();
	worldPos.y *= 2.f * m_extents / (m_aspectRatio * getWindowHeight());
	return worldPos;

}

void PhysicsProjectApp::DrawRect()
{
	m_physicsScene->AddActor(new Sphere(glm::vec2(20, 10), glm::vec2(-10, -17), 1.f, 3, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->AddActor(new Plane(glm::vec2(-0.65, 0.75), -25));

	Box* box1 = new Box(glm::vec2(-20, 0), glm::vec2(16, -4), 1, 4, 8, 4, glm::vec4(1, 0, 0, 1));
	Box* box2 = new Box(glm::vec2(10, 0), glm::vec2(-4, 0), 1, 4, 8, 4, glm::vec4(0, 1, 0, 1));


	box1->SetRotation(0.5);

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);

	box1->ApplyForce(glm::vec2(30, 0), glm::vec2(0));
	box2->ApplyForce(glm::vec2(-15, 0), glm::vec2(0));

	Sphere* ball = new Sphere(glm::vec2(5, -10), glm::vec2(0, 0), 1, 3, glm::vec4(0, 0, 1, 1));
	ball->SetRotation(0.5);
	m_physicsScene->AddActor(ball);
	ball->SetKinematic(true);

}

void PhysicsProjectApp::SphereAndPlane()
{
	//Create objects here
	Sphere* ball1;
	Sphere* ball2;

	ball1 = new Sphere(glm::vec2(-30, 10), glm::vec2(0, 0), 3.f, 5, glm::vec4(1, 0, 0, 1));
	ball2 = new Sphere(glm::vec2(30, 10), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));
	Plane* plane = new Plane();

	//Add actors to the scene here
	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(plane);

	//Apply force to objects here
	ball1->ApplyForce(glm::vec2(30, 0), glm::vec2(0));
	ball2->ApplyForce(glm::vec2(-60, 0), glm::vec2(0));

}

void PhysicsProjectApp::DrawPool()
{
	// Add walls to scene
	Box* leftWall = new Box(glm::vec2(-98, 0), glm::vec2(0, 0), 0, 4, 1, 45, glm::vec4(1, 0, 0, 1));
	Box* rightWall = new Box(glm::vec2(98, 0), glm::vec2(0, 0), 0, 4, 1, 45, glm::vec4(1, 0, 0, 1));

	Box* botLeftWall = new Box(glm::vec2(-48, -54.2), glm::vec2(0, 0), 0, 4, 40, 1, glm::vec4(1, 0, 0, 1));
	Box* botRightWall = new Box(glm::vec2(48, -54.2), glm::vec2(0, 0), 0, 4, 40, 1, glm::vec4(1, 0, 0, 1));

	Box* topLeftWall = new Box(glm::vec2(-48, 54.2), glm::vec2(0, 0), 0, 4, 40, 1, glm::vec4(1, 0, 0, 1));
	Box* topRightWall = new Box(glm::vec2(48, 54.2), glm::vec2(0, 0), 0, 4, 40, 1, glm::vec4(1, 0, 0, 1));

	//Add walls to scene
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

	m_physicsScene->AddActor(botLeftWall);
	m_physicsScene->AddActor(botRightWall);

	m_physicsScene->AddActor(topLeftWall);
	m_physicsScene->AddActor(topRightWall);

	//Set Walls as Kinematic
	leftWall->SetKinematic(true);
	rightWall->SetKinematic(true);

	botLeftWall->SetKinematic(true);
	botRightWall->SetKinematic(true);

	topLeftWall->SetKinematic(true);
	topRightWall->SetKinematic(true);

	//Draw Pockets
	Sphere* topLeftPocket = new Sphere(glm::vec2(-95, 52), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));
	Sphere* botLeftPocket = new Sphere(glm::vec2(-95, -52), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));

	Sphere* topMidPocket = new Sphere(glm::vec2(0, 56), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));
	Sphere* botMidPocket = new Sphere(glm::vec2(0, -56), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));

	Sphere* topRightPocket = new Sphere(glm::vec2(95, 52), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));
	Sphere* botRightPocket = new Sphere(glm::vec2(95, -52), glm::vec2(0, 0), 3.f, 5, glm::vec4(0, 1, 0, 1));


	//Add actor to scene
	m_physicsScene->AddActor(topLeftPocket);
	m_physicsScene->AddActor(botLeftPocket);

	m_physicsScene->AddActor(topMidPocket);
	m_physicsScene->AddActor(botMidPocket);

	m_physicsScene->AddActor(topRightPocket);
	m_physicsScene->AddActor(botRightPocket);


	//Sets Pockets to kinematic
	topLeftPocket->SetKinematic(true);
	botLeftPocket->SetKinematic(true);

	topMidPocket->SetKinematic(true);
	botMidPocket->SetKinematic(true);

	topRightPocket->SetKinematic(true);
	botRightPocket->SetKinematic(true);

	// Set Pockets as triggers
	topLeftPocket->SetTrigger(true);
	botLeftPocket->SetTrigger(true);

	topMidPocket->SetTrigger(true);
	botMidPocket->SetTrigger(true);

	topRightPocket->SetTrigger(true);
	botRightPocket->SetTrigger(true);


	//Draw Pool Balls
	Sphere* cueBall = new Sphere(glm::vec2(-60, 0), glm::vec2(0, 0), 3.f, 3, glm::vec4(1, 1, 1, 1));
	Sphere* ball1 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(28, -5), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball3 = new Sphere(glm::vec2(28, 5), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball4 = new Sphere(glm::vec2(36, 0), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball5 = new Sphere(glm::vec2(36, -10), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball6 = new Sphere(glm::vec2(36, 10), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball7 = new Sphere(glm::vec2(44, -5), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball8 = new Sphere(glm::vec2(44, 5), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball9 = new Sphere(glm::vec2(44, -15), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball10 = new Sphere(glm::vec2(44, 15), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball11 = new Sphere(glm::vec2(52, 0), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball12 = new Sphere(glm::vec2(52, -10), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball13 = new Sphere(glm::vec2(52, 10), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball14 = new Sphere(glm::vec2(52, -20), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));
	Sphere* ball15 = new Sphere(glm::vec2(52, 20), glm::vec2(0, 0), 3.f, 3, glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(cueBall);
	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);
	m_physicsScene->AddActor(ball7);
	m_physicsScene->AddActor(ball8);
	m_physicsScene->AddActor(ball9);
	m_physicsScene->AddActor(ball10);
	m_physicsScene->AddActor(ball11);
	m_physicsScene->AddActor(ball12);
	m_physicsScene->AddActor(ball13);
	m_physicsScene->AddActor(ball14);
	m_physicsScene->AddActor(ball15);

	cueBall->ApplyForce(glm::vec2(200, 0), cueBall->GetPosition());


}

void PhysicsProjectApp::SpringTest(int a_amount)
{
	Sphere* prev = nullptr;

	for (int i = 0; i < a_amount; i++)
	{
		//This will need to spawn the sphere at the bottom of the previous one, to
		// make a pendulum that id affected by gravity
		Sphere* sphere = new Sphere(glm::vec2(i * 3, 30 - i * 5), glm::vec2(0), 10, 2, glm::vec4(0, 0, 1, 1));
		if (i == 0)
		{
			sphere->SetKinematic(true);
		}
		m_physicsScene->AddActor(sphere);

		if (prev)
		{
			m_physicsScene->AddActor(new Spring(sphere, prev, 10, 500));
		}
		prev = sphere;
	}
	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 0.3f, 20, 8, 2, glm::vec4(1, 0, 0, 1));
	box->SetKinematic(true);

	m_physicsScene->AddActor(box);


}

void PhysicsProjectApp::TriggerTest()
{
	Sphere* ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0), 4, 4, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(10, -20), glm::vec2(0), 4, 4, glm::vec4(0, 0.5, 0.5, 1));

	ball2->SetKinematic(true);
	ball2->SetTrigger(true);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -30));
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -50));
	m_physicsScene->AddActor(new Plane(glm::vec2(-1, 0), -50));
	m_physicsScene->AddActor(new Box(glm::vec2(20, 10), glm::vec2(10, 0), 0.5, 4, 8, 4));
	m_physicsScene->AddActor(new Box(glm::vec2(-40, 10), glm::vec2(10, 0), 0.5, 4, 8, 4));

	ball2->m_triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered" << other << std::endl; };
	ball2->m_triggerExit = [=](PhysicsObject* other) {std::cout << "Exited" << other << std::endl; };



}
