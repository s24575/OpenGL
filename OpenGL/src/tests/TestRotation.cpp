#include "TestRotation.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestRotation::TestRotation()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, -500.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		m_Translation(480.0f, 270.0f, 200.0f),
		m_CurrentTime(0.0f),
		m_ScaleFactor(200.0f)
	{
		float positions[] = {
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,	0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,	0.5f, -0.5f
		};


		// sides: front, back, left, right, top, bottom
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

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_DEPTH_TEST));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 3 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, 6 * 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Rotate.shader");
	}

	TestRotation::~TestRotation()
	{

	}

	void TestRotation::OnUpdate(float deltaTime)
	{
		m_CurrentTime += deltaTime;
	}

	void TestRotation::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer; 

		glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_ScaleFactor));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation) * scalingMatrix;
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

	}

	void TestRotation::OnImGuiRender()
	{
		ImGui::SliderFloat("Distance", &m_Translation.z, 0.0f, 500.0f);
		ImGui::SliderFloat("Scale", &m_ScaleFactor, 0.0f, 540.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}