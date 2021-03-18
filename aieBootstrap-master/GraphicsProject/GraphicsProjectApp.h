#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "OBJMesh.h"
#include <vector>
#include"Scene.h"

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
	std::vector<Camera> m_cameraArray;
	int m_cameraArraySize = 0;
	int m_cameraNumber = 0;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	// SHADER
	aie::ShaderProgram m_simpleShader;
	aie::ShaderProgram m_bunnyShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_textureShader;
	aie::ShaderProgram m_normalMapShader;
	aie::ShaderProgram m_newMapShader;



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

	//Create a soulspear
	aie::OBJMesh m_spearMesh;
	glm::mat4 m_spearTransform;
	glm::vec3 m_spearPosition{ 0,0,0 };

	aie::OBJMesh m_coltMesh;
	glm::mat4 m_coltTransform;
	glm::vec3 m_coltPosition{ 0,0,0 };

	/*struct Light
	{
		glm::vec3 color;
		glm::vec3 direction;
	};*/
	int numberOfLights = 4;
	glm::vec3 m_ambientLight;

	Scene* m_scene;
	

	/*Light m_light;
	Light* m_light1 = new Light();*/


public:
	void CameraLocations();
	bool LoadShaderAndMeshLogic(Light a_light);
	//void DrawShaderAndMeshes(glm::mat4, glm::mat4);
	void IMGUI_Logic();


};