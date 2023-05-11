#include "Cube.h"

Cube::Cube()
	: m_VAO(std::make_unique<VertexArray>()),
	m_Translation(0.0f, 0.0f, 0.0f)
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

	unsigned int indicies[] = {
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

	m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, sizeof(indicies) / sizeof(unsigned int));
}

Cube::~Cube()
{

}