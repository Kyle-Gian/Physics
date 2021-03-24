#pragma once
#include <glm/glm.hpp>

class Camera;
class Scene;

namespace aie
{
	class OBJMesh;
	class ShaderProgram;
}
class Instance
{
public:
	Instance(glm::mat4 a_transform, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);
	Instance(char* a_name, glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);

	void Draw(Scene* a_scene);

	static glm::mat4 MakeTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale);
	void UpdateTransform();
	char* GetString() { return m_name; }

	glm::vec3 m_position;
	glm::vec3 m_eulerAngles;
	glm::vec3 m_scale;
	glm::mat4 m_transform;

protected:

	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;
	char* m_name;


};

