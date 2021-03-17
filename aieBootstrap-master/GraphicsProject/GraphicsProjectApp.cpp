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

	/*for (size_t i = 0; i < numberOfLights; i++)
	{
		delete m_light[i];
	}*/

}

bool GraphicsProjectApp::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);




	m_cameraArray.push_back(m_camera);

	//for (size_t i = 0; i < numberOfLights; i++)
	//{
	//	m_light[i] = new Light();
	//	m_light[i]->color = { 1,1,0 };
	//	m_light[i]->direction = glm::vec3(-1 + i, 0, 0);
	//	m_light[i]->m_ambientLight = { 0.25f,0.25f,0.25f };
	//}

	m_light.color = glm::vec3(1, 1, 0);
	m_light.direction = glm::vec3(1, 0, 1);
	m_light.m_ambientLight = { 0.25f,0.25f,0.25f };

	m_light1->color = { 1,1,0 };
	m_light1->direction = glm::vec3(-1, 0, -1);
	m_light1->m_ambientLight = { 0.25f,0.25f,0.25f };

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

void GraphicsProjectApp::CameraLocations()
{
	aie::Input* input = aie::Input::getInstance();


	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{

	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{

	}



}

bool GraphicsProjectApp::LoadShaderAndMeshLogic()
{
#pragma region LoadShadersFromFile

#pragma region QuadShader

	// Load the Vertex shader from a file
	//m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load the fragment shader from a file
	//m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	//if (!m_simpleShader.link())
	//{
		//printf("Simple Shader had an error: %s\n", m_simpleShader.getLastError());
		//return false;
	//}


#pragma endregion

#pragma region BunnyShader
	// Load the Vertex shader from a file
	//m_bunnyShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	////Load the fragment shader from a file
	//m_bunnyShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	//if (!m_bunnyShader.link())
	//{
	//	printf("Bunny Shader had an error: %s\n", m_bunnyShader.getLastError());
	//	return false;

	//}
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


#pragma region TextureShader

	m_textureShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_textureShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");

	if (!m_textureShader.link())
	{
		printf("Texture Shader had an error: %s\n", m_textureShader.getLastError());
		return false;

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
#pragma region NewShader

	/*m_newMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/newShader.vert");
	m_newMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/newShader.frag");

	if (!m_newMapShader.link())
	{
		printf("Normal Map Shader had an error: %s\n", m_newMapShader.getLastError());
		return false;

	}*/
#pragma endregion



#pragma endregion


#pragma region CreateObject

#pragma region BunnyLogic
	////Load the file as a mesh
	//if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	//{
	//	printf("Bunny Mesh Failed!\n");
	//	return false;
	//}
	////Give a Transform for Bunny with scale being set
	//m_bunnyTransform = {
	//	0.5f,0,0,0,
	//	0,0.5f,0,0,
	//	0,0,0.5f,0,
	//	0,0,0,1
	//};

#pragma endregion

#pragma region DragonLogic
	//Load the file as a mesh
	//if (m_dragonMesh.load("./stanford/dragon.obj") == false)
	//{
	//	printf("Dragon Mesh Failed!\n");
	//	return false;
	//}

	////Give a Transform for Dragon with scale being set
	//m_dragonTransform = {
	//	0.5f,0,0,0,
	//	0,0.5f,0,0,
	//	0,0,0.5f,0,
	//	0,0,0,1
	//};

#pragma region BuddhaLogic
	//Load the file as a mesh
	//if (m_buddhaMesh.load("./stanford/buddha.obj") == false)
	//{
	//	printf("Buddha Mesh Failed!\n");
	//	return false;
	//}
	////Give a Transform for Buddha with scale being set
	//m_buddhaTransform = {
	//	0.5f,0,0,0,
	//	0,0.5f,0,0,
	//	0,0,0.5f,0,
	//	0,0,0,1
	//};
#pragma endregion

#pragma region LucyLogic
	//Load the file as a mesh
	//if (m_lucyMesh.load("./stanford/lucy.obj") == false)
	//{
	//	printf("Lucy Mesh Failed!\n");
	//	return false;
	//}
	////Give a Transform for Lucy with scale being set
	//m_lucyTransform = {
	//	0.5f,0,0,0,
	//	0,0.5f,0,0,
	//	0,0,0.5f,0,
	//	0,0,0,1
	//};
#pragma endregion


#pragma endregion

#pragma region QuadLogic



	//Define the 6 vertices  for the 2 triangles that make the quad
/*Mesh::Vertex verticesNoIndex[6];
verticesNoIndex[0].position = { -0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[1].position = { 0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[2].position = { -0.5f, 0.f, -0.5f, 1.f };

verticesNoIndex[3].position = { -0.5f, 0.f, -0.5f, 1.f };
verticesNoIndex[4].position = { 0.5f, 0.f, 0.5f, 1.f };
verticesNoIndex[5].position = { 0.5f, 0.f, -0.5f, 1.f };*/

//Mesh::Vertex vertices[4];
//vertices[0].position = { -0.5f, 0.f, 0.5f, 1.f };
//vertices[1].position = { 0.5f, 0.f, 0.5f, 1.f };
//vertices[2].position = { -0.5f, 0.f, -0.5f, 1.f };
//vertices[3].position = { 0.5f, 0.f, -0.5f, 1.f };

//unsigned int indices[6] = { 0,1,2,2,1,3 };

//m_quadMesh.Initialise(4, vertices, 6, indices);

////We will make the quad 10 units by 10 units
//m_quadTransform = {
//	10,0,0,0,
//	0,10,0,0,
//	0,0,10,0,
//	0,0,0,1
//};
//m_quadTransform = glm::rotate(m_quadTransform, 3.14f / 2, glm::vec3(1, 0, 0));
#pragma endregion

#pragma region ColtLogic
//Load the file as a mesh
	if (m_coltMesh.load("./colt/source/colt.obj") == false)
	{
		printf("Colt Mesh Failed!\n");
		return false;
	}

	//Give a Transform for Dragon with scale being set
	m_coltTransform = {
		0.01f,0,0,0,
		0,0.01f,0,0,
		0,0,0.01f,0,
		0,0,0,1
	};
#pragma endregion



#pragma endregion

	return true;
}

void GraphicsProjectApp::DrawShaderAndMeshes(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
{
	auto pvm = a_projectionMatrix * a_viewMatrix * glm::mat4(0);


#pragma region Quad
	//Bind the shader
	//m_textureShader.bind();

	////Bind the transforms of the mesh

	//pvm = a_projectionMatrix * a_viewMatrix * m_quadTransform; //PVM = Projection View Matrix
	//m_textureShader.bindUniform("ProjectionViewModel", pvm);

	//m_textureShader.bindUniform("diffuseTexture", 0);

	////Bind the texture to the specified location
	//m_gridTexture.bind(0);

	////Draw the Quad...
	//m_quadMesh.Draw();
#pragma endregion

#pragma region Phong
//Bind the shader
	//m_phongShader.bind();

	////Bind the camera Position
	//m_phongShader.bindUniform("CameraPosition", vec3(glm::inverse(a_viewMatrix)[3]));

	////Bind the light
	//m_phongShader.bindUniform("AmbientColor", m_ambientLight);
	//m_phongShader.bindUniform("LightColor", m_light.color);
	//m_phongShader.bindUniform("LightDirection", m_light.direction);

	//m_phongShader.bindUniform("ProjectionViewModel", pvm);

#pragma endregion

#pragma region Bunny
	//pvm = a_projectionMatrix * a_viewMatrix * m_bunnyTransform;
	////Bind the PVM
	//m_phongShader.bindUniform("ProjectionViewModel", pvm);
	////Bind the lighting Transforms
	//m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

	//// Draw bunny Mesh

	//m_bunnyMesh.draw();

#pragma endregion

#pragma region Dragon
	//pvm = a_projectionMatrix * a_viewMatrix * m_dragonTransform;
	////Bind the PVM
	//m_phongShader.bindUniform("ProjectionViewModel", pvm);
	////Bind the lighting Transforms
	//m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);

	////Draw the dragon
	//m_dragonMesh.draw();


#pragma endregion


#pragma region Lucy
	//pvm = a_projectionMatrix * a_viewMatrix * m_lucyTransform;
	////Bind the PVM
	//m_phongShader.bindUniform("ProjectionViewModel", pvm);
	////Bind the lighting Transforms
	//m_phongShader.bindUniform("ModelMatrix", m_lucyTransform);

	////Draw Lucy
	//m_lucyMesh.draw();
#pragma endregion


#pragma region Buddha
	//pvm = a_projectionMatrix * a_viewMatrix * m_buddhaTransform;
	////Bind the PVM
	//m_phongShader.bindUniform("ProjectionViewModel", pvm);
	////Bind the lighting Transforms
	//m_phongShader.bindUniform("ModelMatrix", m_buddhaTransform);

	////Draw the buddha
	//m_buddhaMesh.draw();
#pragma endregion


#pragma region SoulSpear
	//m_normalMapShader.bind();
	//pvm = a_projectionMatrix * a_viewMatrix * m_spearTransform;
	////Bind the PVM
	//m_normalMapShader.bindUniform("ProjectionViewModel", pvm);

	//m_normalMapShader.bindUniform("CameraPosition", m_camera.GetPosition());
	//m_normalMapShader.bindUniform("AmbientColor", m_ambientLight);
	//m_normalMapShader.bindUniform("LightColor", m_light.color);
	//m_normalMapShader.bindUniform("LightDirection", m_light.direction);

	////Bind the lighting Transforms
	//m_normalMapShader.bindUniform("ModelMatrix", m_spearTransform);

	////Draw the buddha
	//m_spearMesh.draw();
#pragma endregion

#pragma region Colt
	m_normalMapShader.bind();
	pvm = a_projectionMatrix * a_viewMatrix * m_coltTransform;
	//Bind the PVM
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	m_normalMapShader.bindUniform("CameraPosition", m_camera.GetPosition());

	m_normalMapShader.bindUniform("AmbientColor", m_light.m_ambientLight);
	m_normalMapShader.bindUniform("LightColor", m_light.color);
	m_normalMapShader.bindUniform("LightDirection", m_light.direction);

	m_normalMapShader.bindUniform("AmbientColor1", m_light1->m_ambientLight);
	m_normalMapShader.bindUniform("LightColor1", m_light1->color);
	m_normalMapShader.bindUniform("LightDirection1", m_light1->direction);

	//m_newMapShader.bindUniform("NumberOfLights", numberOfLights);

	//for (size_t i = 0; i < numberOfLights; i++)
	//{
	//	m_newMapShader.bindUniform("AmbientColor", numberOfLights, &m_light[i]->m_ambientLight);
	//	m_newMapShader.bindUniform("LightColor",numberOfLights, &m_light[i]->color);
	//	m_newMapShader.bindUniform("LightDirection",numberOfLights, &m_light[i]->direction);
	//}

	//Bind the lighting Transforms
	m_normalMapShader.bindUniform("ModelMatrix", m_coltTransform);

	//Draw the buddha
	m_coltMesh.draw();
#pragma endregion

}

void GraphicsProjectApp::IMGUI_Logic()
{
	ImGui::Begin("Scene Light Settings");

	ImGui::DragFloat3("Sunlight Direction 1", &m_light.direction[0], 0.1f, -10.f, 10.f);
	ImGui::DragFloat3("Sunlight Color 1", &m_light.color[0], 0.1f, 0.f, 2.f);

	ImGui::DragFloat3("Sunlight Direction 2", &m_light1->direction[0], 0.1f, -10.f, 10.f);

	ImGui::DragFloat3("Sunlight Color 2", &m_light1->color[0], 0.1f, 0.f, 2.f);

	ImGui::End();

	//Change the position of the objects with the GUI
	ImGui::Begin("Position For Objects");

	//ImGui::DragFloat3("Bunny Position", &m_bunnyTransform[3][0], 1.f, -20, 20.f);
	//ImGui::DragFloat3("Dragon Position", &m_dragonTransform[3][0], 1.f, -20.f, 20.f);
	//ImGui::DragFloat3("Buddha Position", &m_buddhaTransform[3][0], 1.f, -20.f, 20.f);
	//ImGui::DragFloat3("Lucy Position", &m_lucyTransform[3][0], 1.f, -20.f, 20.f);
	ImGui::DragFloat3("Colt Position", &m_coltTransform[3][0], 1.f, -20.f, 20.f);


	ImGui::End();

	ImGui::Begin("Camera's ");

	ImGui::End();

}
