#include "TestRotation.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestRotation::TestRotation()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, -500.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		m_CurrentTime(0.0f),
		m_ScaleFactor(200.0f)
	{
		cube.setTranslation(480, 270, 200);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_DEPTH_TEST));

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
		glm::mat4 model = glm::translate(glm::mat4(1.0f), cube.getTranslation()) * scalingMatrix;
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		renderer.Draw(cube);
	}

	void TestRotation::OnImGuiRender()
	{
		ImGui::SliderFloat("Distance", &cube.getTranslation().z, 0.0f, 500.0f);
		ImGui::SliderFloat("Scale", &m_ScaleFactor, 0.0f, 540.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}