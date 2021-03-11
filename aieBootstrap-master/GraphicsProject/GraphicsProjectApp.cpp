#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <imgui.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsProjectApp::GraphicsProjectApp() {

}

GraphicsProjectApp::~GraphicsProjectApp() {

}

bool GraphicsProjectApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	m_light.color = { 1,1,0 };
	m_ambientLight = { 0.25f,0.25f,0.25f };
	return LoadShaderAndMeshLogic();
}

void GraphicsProjectApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsProjectApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}


	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	m_camera.Update(deltaTime);

	// Change the positions by a given vector3 set by the GUI. Used for the translate GUI
	//Moves object each frame by that vector
	m_bunnyTransform = glm::translate(m_bunnyTransform, m_bunnyPosition);
	m_dragonTransform = glm::translate(m_dragonTransform, m_dragonPosition);
	m_buddhaTransform = glm::translate(m_buddhaTransform, m_buddhaPosition);
	m_lucyTransform = glm::translate(m_lucyTransform, m_lucyPosition);


	IMGUI_Logic();

	float time = getTime();

	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void GraphicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	glm::mat4 projectionMatrix = m_camera.GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_camera.GetViewMatrix();

	DrawShaderAndMeshes(projectionMatrix, viewMatrix);
	// update perspective based on screen size
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	Gizmos::draw(projectionMatrix * viewMatrix);

}

void GraphicsProjectApp::DrawPlanets()
{
	glm::vec3 sun = glm::vec3(0, 0, 0);
	glm::vec3 mercury = glm::vec3(5);

	float mercuryRing = 0.f;

	mercuryRing = glm::distance(sun, mercury);


	Gizmos::addSphere(sun, 1, 16, 16, glm::vec4(0.4f, 0.5f, 0, 1));


	Gizmos::addSphere(glm::vec3(cos(0.5f * getTime()), 0, sin(0.5f * getTime())) + mercury, 0.1f, 10, 10, glm::vec4(0.5f, 0, 0, 1));

}

bool GraphicsProjectApp::LoadShaderAndMeshLogic()
{
#pragma region LoadShadersFromFile

#pragma region QuadShader

	// Load the Vertex shader from a file
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load the fragment shader from a file
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (!m_simpleShader.link())
	{
		printf("Simple Shader had an error: %s\n", m_simpleShader.getLastError());
		return false;
	}


#pragma endregion

#pragma region BunnyShader
	// Load the Vertex shader from a file
	m_bunnyShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load the fragment shader from a file
	m_bunnyShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (!m_bunnyShader.link())
	{
		printf("Bunny Shader had an error: %s\n", m_bunnyShader.getLastError());
		return false;

	}
#pragma region DragonShader
	// Load the Vertex shader from a file
	//m_dragonShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load the fragment shader from a file
	//m_dragonShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	//if (!m_bunnyShader.link())
	//{
	//	printf("Bunny Shader had an error: %s\n", m_dragonShader.getLastError());
	//	return false;

	//}
#pragma endregion

#pragma endregion

#pragma endregion

#pragma region Phong

	//Load the Vertex script
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	//Load the Fragment Script
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	//If these files do not link up eg missing break and give error
	if (m_phongShader.link() == false)
	{
		printf("Phong shader had an error: %s\n", m_phongShader.getLastError());
		false;
	}


#pragma endregion

#pragma region CreateObject

#pragma region BunnyLogic
	//Load the file as a mesh
	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Failed!\n");
		return false;
	}
	//Give a Transform for Bunny with scale being set
	m_bunnyTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

#pragma endregion

#pragma region DragonLogic
	//Load the file as a mesh
	if (m_dragonMesh.load("./stanford/dragon.obj") == false)
	{
		printf("Dragon Mesh Failed!\n");
		return false;
	}

	//Give a Transform for Dragon with scale being set
	m_dragonTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

#pragma region BuddhaLogic
	//Load the file as a mesh
	if (m_buddhaMesh.load("./stanford/buddha.obj") == false)
	{
		printf("Buddha Mesh Failed!\n");
		return false;
	}
	//Give a Transform for Buddha with scale being set
	m_buddhaTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};
#pragma endregion

#pragma region LucyLogic
	//Load the file as a mesh
	if (m_lucyMesh.load("./stanford/lucy.obj") == false)
	{
		printf("Lucy Mesh Failed!\n");
		return false;
	}
	//Give a Transform for Lucy with scale being set
	m_lucyTransform = {
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};
#pragma endregion


#pragma endregion


#pragma region QuadLogic
	//m_quadMesh.InitialiseQuad();



	//Define the 6 vertices  for the 2 triangles that make the quad
/*Mesh::Vertex verticesNoIndex[6];
verticesNoIndex[0].position = { -0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[1].position = { 0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[2].position = { -0.5f, 0.f, -0.5f, 1.f };

verticesNoIndex[3].position = { -0.5f, 0.f, -0.5f, 1.f };
verticesNoIndex[4].position = { 0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[5].position = { 0.5f, 0.f, -0.5f, 1.f };*/

	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0.f, 0.5f, 1.f };
	vertices[1].position = { 0.5f, 0.f, 0.5f, 1.f };
	vertices[2].position = { -0.5f, 0.f, -0.5f, 1.f };
	vertices[3].position = { 0.5f, 0.f, -0.5f, 1.f };

	unsigned int indices[6] = { 0,1,2,2,1,3 };

	m_quadMesh.Initialise(4, vertices, 6, indices);

	//We will make the quad 10 units by 10 units
	m_quadTransform = {
		10,0,0,0,
		0,10,0,0,
		0,0,10,0,
		0,0,0,1
	};
	m_quadTransform = glm::rotate(m_quadTransform, 3.14f / 2, glm::vec3(1, 0, 0));
#pragma endregion

#pragma endregion

	return true;
}

void GraphicsProjectApp::DrawShaderAndMeshes(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
{
	auto pvm = a_projectionMatrix * a_viewMatrix * glm::mat4(0);


#pragma region Quad
	//Bind the shader
	//m_simpleShader.bind();

	//Bind the transforms of the mesh

	//pvm = a_projectionMatrix * a_viewMatrix * m_quadTransform; //PVM = Projection View Matrix
	//m_simpleShader.bindUniform("ProjectionViewModel", pvm);

	//m_quadMesh.Draw();
#pragma endregion

#pragma region Phong
//Bind the shader
	m_phongShader.bind();

	//Bind the camera Position
	m_phongShader.bindUniform("CameraPosition", vec3(glm::inverse(a_viewMatrix)[3]));

	//Bind the light
	m_phongShader.bindUniform("AmbientColor", m_ambientLight);
	m_phongShader.bindUniform("LightColor", m_light.color);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	m_phongShader.bindUniform("ProjectionViewModel", pvm);

#pragma endregion

#pragma region Bunny
	pvm = a_projectionMatrix * a_viewMatrix * m_bunnyTransform;
	//Bind the PVM
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	//Bind the lighting Transforms
	m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

	// Draw bunny Mesh

	m_bunnyMesh.draw();

#pragma endregion

#pragma region Dragon
	pvm = a_projectionMatrix * a_viewMatrix * m_dragonTransform;
	//Bind the PVM
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	//Bind the lighting Transforms
	m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);

	//Draw the dragon
	m_dragonMesh.draw();


#pragma endregion


#pragma region Lucy
	pvm = a_projectionMatrix * a_viewMatrix * m_lucyTransform;
	//Bind the PVM
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	//Bind the lighting Transforms
	m_phongShader.bindUniform("ModelMatrix", m_lucyTransform);

	//Draw Lucy
	m_lucyMesh.draw();
#pragma endregion


#pragma region Buddha
	pvm = a_projectionMatrix * a_viewMatrix * m_buddhaTransform;
	//Bind the PVM
	m_phongShader.bindUniform("ProjectionViewModel", pvm);
	//Bind the lighting Transforms
	m_phongShader.bindUniform("ModelMatrix", m_buddhaTransform);

	//Draw the buddha
	m_buddhaMesh.draw();
#pragma endregion


}

void GraphicsProjectApp::IMGUI_Logic()
{
	ImGui::Begin("Scene Light Settings");

	ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -1.f, 1.f);
	ImGui::DragFloat3("Sunlight Color", &m_light.color[0], 0.1f, 0.f, 2.f);

	ImGui::End();

	//Change the position of the objects with the GUI
	ImGui::Begin("Position For Objects");

	ImGui::DragFloat3("Bunny Position", &m_bunnyTransform[3][0], 1.f, -20, 20.f);
	ImGui::DragFloat3("Dragon Position", &m_dragonTransform[3][0], 1.f, -20.f, 20.f);
	ImGui::DragFloat3("Buddha Position", &m_buddhaTransform[3][0], 1.f, -20.f, 20.f);
	ImGui::DragFloat3("Lucy Position", &m_lucyTransform[3][0], 1.f, -20.f, 20.f);

	ImGui::End();

	/*ImGui::Begin("Transform For Objects");

	ImGui::DragFloat3("Bunny Transform", &m_bunnyPosition[0], 0.001f, -2.f, 2.f);
	ImGui::DragFloat3("Dragon Transform", &m_dragonPosition[0], 0.001f, -2.f, 2.f);
	ImGui::DragFloat3("Buddha Transform", &m_buddhaPosition[0], 0.001f, -2.f, 2.f);
	ImGui::DragFloat3("Lucy Transform", &m_lucyPosition[0], 0.001f, -2.f, 2.f);

	ImGui::End();*/

}
