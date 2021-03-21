#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <imgui.h>

#include "Scene.h"
#include "Instance.h"
#include <iostream>

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

	m_cameraArray.push_back(m_camera);

	m_cameraArray.push_back(m_camera1);
	m_cameraArray.push_back(m_camera2);



	Light light = Light(vec3(1, 1, 1), vec3(1, 1, 1), 1.f);


	return LoadShaderAndMeshLogic(light);
}

void GraphicsProjectApp::shutdown() {

	Gizmos::destroy();
	delete m_scene;

	for (size_t i = 0; i < m_cameraArray.size(); i++)
	{
		delete m_cameraArray[i];
	}

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

	Inputs();

	IMGUI_Logic();

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

	m_scene->Draw();

	Gizmos::draw(projectionMatrix * viewMatrix);

}

void GraphicsProjectApp::Inputs()
{
	aie::Input* input = aie::Input::getInstance();

	int instancesSize = 0;
	int cameraSize = 0;
	instancesSize = m_scene->GetInstances().size();
	cameraSize = m_cameraArray.size();

	//If the UP key has been pressed and the number isn't greater then the vector size increase the vector position

	if (m_objectPos != instancesSize - 1)
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_UP))
		{
			m_objectPos++;
		}
	}
	//If the DOWN key has been pressed and the number isn't greater then the vector size decrease the vector position

	if (m_objectPos > 0)
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		{
			m_objectPos--;

		}
	}


	if (m_cameraNumber != cameraSize - 1)
	{
		//If the E key has been pressed and the number isn't greater then increase camera size to change camera
		if (input->wasKeyPressed(aie::INPUT_KEY_E))
		{
			m_cameraNumber++;
		}
	}
	//If the Q key has been pressed and the number isn't greater then increase camera size to change camera
	if (m_cameraNumber > 0)
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_Q))
		{
			m_cameraNumber--;

		}
	}
	
}

bool GraphicsProjectApp::LoadShaderAndMeshLogic(Light a_light)
{
#pragma region LoadShadersFromFile

#pragma region PhongShader

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

#pragma region NormalMapShader
	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalMap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalMap.frag");

	if (!m_normalMapShader.link())
	{
		printf("Normal Map Shader had an error: %s\n", m_normalMapShader.getLastError());
		return false;

	}
#pragma endregion

#pragma endregion


#pragma region CreateObject

#pragma region BunnyLogic
	////Load the file as a mesh
	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny Mesh Failed!\n");
		return false;
	}

#pragma endregion

#pragma region SpearLogic
	//Load the file as a mesh
	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("Spear Mesh Failed!\n");
		return false;
	}

#pragma endregion


#pragma region ColtLogic
	//Load the file as a mesh
	if (m_coltMesh.load("./colt/source/colt.obj", true, true) == false)
	{
		printf("Colt Mesh Failed!\n");
		return false;
	}

#pragma endregion


#pragma endregion
	m_scene = new Scene(&m_camera, glm::vec2(getWindowWidth(), getWindowHeight()), a_light, glm::vec3(0.25f));

	m_scene->AddInstances(new Instance("Spear", glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1), &m_spearMesh, &m_normalMapShader));

	m_scene->AddInstances(new Instance("Colt", glm::vec3(-2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.01f), &m_coltMesh, &m_normalMapShader));

	m_scene->AddInstances(new Instance("Bunny", glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0.5f), &m_bunnyMesh, &m_phongShader));


	m_scene->GetPointLights().push_back(Light(vec3(5, 3, 0), vec3(0, 1, 0), 10));
	m_scene->GetPointLights().push_back(Light(vec3(-5, 3, 0), vec3(1, 0, 0), 10));

	return true;
}

void GraphicsProjectApp::IMGUI_Logic()
{

	ImGui::Begin("Scene Light Settings");

	ImGui::DragFloat3("Sunlight Direction 1", &m_scene->GetLight().m_direction[0], 0.1f, -10.f, 10.f);
	ImGui::DragFloat3("Sunlight Color 1", &m_scene->GetLight().m_color[0], 0.1f, 0.f, 2.f);

	//ImGui::DragFloat3("Sunlight Direction 2", &m_light1->direction[0], 0.1f, -10.f, 10.f);

	//ImGui::DragFloat3("Sunlight Color 2", &m_light1->color[0], 0.1f, 0.f, 2.f);

	ImGui::End();



	//Change the position, rotation and scale of the objects with the GUI
	if (m_scene->GetInstances().size() != NULL)
	{
		ImGui::Begin("Position For Objects");
		ImGui::DragFloat3(m_scene->GetInstances()[m_objectPos]->GetString(), &m_scene->GetInstances()[m_objectPos]->m_position[0], 0.5f, -20, 20.f);
		ImGui::End();

		ImGui::Begin("Rotation For Objects");
		ImGui::DragFloat3(m_scene->GetInstances()[m_objectPos]->GetString(), &m_scene->GetInstances()[m_objectPos]->m_eulerAngles[0], 1.f, -90, 90.f);
		ImGui::End();

		ImGui::Begin("Scale For Objects");
		ImGui::DragFloat3(m_scene->GetInstances()[m_objectPos]->GetString(), &m_scene->GetInstances()[m_objectPos]->m_scale[0], .1f, 0, 2.f);
		ImGui::End();

		m_scene->GetInstances()[m_objectPos]->UpdateTransform();  
	}

	ImGui::Begin("Camera's ");

	ImGui::DragFloat3("Camera " + m_cameraNumber, &m_cameraArray[m_cameraNumber].GetPosition()[0], 1.f, -20, 20.f);


	ImGui::End();

}
