#include "Cube.h"

#include "glm/gtc/matrix_transform.hpp"

Cube::Cube()
	: m_VAO(std::make_unique<VertexArray>()),
	m_Translation(0.0f, 0.0f, 0.0f),
	m_ScaleFactor(1.0f)
{
	float vertices[] = {
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,	0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,	0.5f, -0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		4, 0, 3,
		3, 7, 4,
		5, 1, 2,
		2, 6, 5,
		3, 2, 6,
		6, 7, 3,
		0, 1, 5,
		5, 4, 0
	};

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	m_VAO->AddBuffer(*m_VertexBuffer, layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));

	m_Shader = std::make_unique<Shader>("res/shaders/Rotate.shader");
}

Cube::~Cube()
{

}

void Cube::update(const glm::mat4& view, const glm::mat4& proj, float currentTime)
{
	glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_ScaleFactor));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation) * scalingMatrix;
	glm::mat4 mvp = proj * view * model;
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform1f("u_Delta", currentTime);
}

void Cube::draw()
{
	m_Shader->Bind();
	m_VAO->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, getVerticesCount(), GL_UNSIGNED_INT, nullptr));
}