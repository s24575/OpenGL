#pragma once

#include "glm/vec3.hpp"

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

class Plane
{
public:
	Plane();
	~Plane();

	void draw();

	Shader* getShader() const { return m_Shader.get(); }
	unsigned int getVerticesCount() const { return m_IndexBuffer->GetCount(); }
	glm::vec3& getTranslation() { return m_Translation; }
	glm::vec3 getTranslation() const { return m_Translation; }
	void setTranslation(float x, float y, float z)
	{
		m_Translation.x = x;
		m_Translation.y = y;
		m_Translation.z = z;
	}
private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;

	glm::vec3 m_Translation;
};