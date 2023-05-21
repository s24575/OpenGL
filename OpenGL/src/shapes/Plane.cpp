#include "Plane.h"

Plane::Plane()
	: m_VAO(std::make_unique<VertexArray>()),
	m_Translation(0.0f, 0.0f, 0.0f)
{
	float vertices[] = {
		-0.5f, 0.0f,  0.5f,
		 0.5f, 0.0f,  0.5f,
		 0.5f, 0.0f, -0.5f,
		-0.5f, 0.0f, -0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

	m_Shader = std::make_unique<Shader>("res/shaders/Scenery.shader");

	//m_IndexBuffer->Bind();
}

Plane::~Plane()
{

}

void Plane::draw()
{
	m_Shader->Bind();
	m_VAO->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, getVerticesCount(), GL_UNSIGNED_INT, nullptr));
}