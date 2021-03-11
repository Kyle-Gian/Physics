#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"

class GraphicsProjectApp : public aie::Application {
public:

	GraphicsProjectApp();
	virtual ~GraphicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void DrawPlanets();

protected:

	Camera m_camera;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	// SHADER
	aie::ShaderProgram m_simpleShader;
	aie::ShaderProgram m_bunnyShader;
	aie::ShaderProgram m_phongShader;

	//
	//Basic Plane
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	//Create a bunny with a flat color
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	glm::vec3 m_bunnyPosition{ 0,0,0 };

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;
	glm::vec3 m_dragonPosition{ 0,0,0 };


	aie::OBJMesh m_lucyMesh;
	glm::mat4 m_lucyTransform;
	glm::vec3 m_lucyPosition{ 0,0,0 };


	aie::OBJMesh m_buddhaMesh;
	glm::mat4 m_buddhaTransform;
	glm::vec3 m_buddhaPosition{ 0,0,0 };


	struct Light
	{
		glm::vec3 color;
		glm::vec3 direction;
	};

	Light m_light;

	glm::vec3 m_ambientLight;
public:
	bool LoadShaderAndMeshLogic();
	void DrawShaderAndMeshes(glm::mat4, glm::mat4);
	void IMGUI_Logic();
};