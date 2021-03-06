//Author Kyle Gian
//Date Created 10/3/2021
//Last Modified 10/3/2021

//Creates a mesh based off given data and uses tri's to creat the mesh 


#pragma once
#include <glm/glm.hpp>
class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0){}
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void InitialiseQuad();
	void InitialiseFullscreenQuad();
	void Initialise(unsigned int a_vertexCount, const Vertex* a_vertices, unsigned int a_indexCount = 0, unsigned int* a_indices = nullptr);

	virtual void Draw();
protected:
	unsigned int triCount;
	unsigned int vao, // Vertex array object
				 vbo, //vertex buffer object
				 ibo;// Index buffer object
};

