#include "TestScenery.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"

namespace test {

	TestScenery::TestScenery()
		: m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 5.0f))),
		m_Translation(0.0f, 0.0f, 250.0f),
		m_CurrentTime(0.0f),
		m_ScaleFactor(100.0f)
	{
		//m_View = glm::rotate(m_View, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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

		//unsigned int planeVertices[] = {
		//	-0.5f, 0.0f,  0.5f,
		//	 0.5f, 0.0f,  0.5f,
		//	 0.5f, 0.0f, -0.5f,
		//	-0.5f, 0.0f, -0.5f,
		//};

		unsigned int planeVertices[] = {
			-0.5f, -0.5f, 0.5f,
			 0.5f, -0.5f, 0.5f,
			 0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
		};

		unsigned int planeIndicies[] = {
			0, 1, 2,
			2, 3, 0
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

		// Plane
		m_PlaneScaleFactor = 100.0f;

		m_PlaneTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

		m_PlaneVAO = std::make_unique<VertexArray>();

		m_PlaneVertexBuffer = std::make_unique<VertexBuffer>(planeVertices, 4 * 3 * sizeof(float));
		VertexBufferLayout planeLayout;
		planeLayout.Push<float>(3);
		m_PlaneVAO->AddBuffer(*m_PlaneVertexBuffer, planeLayout);

		m_PlaneIndexBuffer = std::make_unique<IndexBuffer>(planeVertices, 6);

		m_PlaneShader = std::make_unique<Shader>("res/shaders/Scenery.shader");
	}

	TestScenery::~TestScenery()
	{

	}

	void TestScenery::OnUpdate(float deltaTime)
	{
		m_CurrentTime += deltaTime;
	}

	void TestScenery::OnRender()
	{
		GLCall(glClearColor(0.53f, 0.81f, 0.92f, 0.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;

		//glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_ScaleFactor));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation) * scalingMatrix;
		//glm::mat4 mvp = m_Proj * m_View * model;
		//m_Shader->Bind();
		//m_Shader->SetUniformMat4f("u_MVP", mvp);
		//m_Shader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		//renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);


		glm::mat4 planeScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_PlaneScaleFactor));
		glm::mat4 planeModel = glm::translate(glm::mat4(1.0f), m_PlaneTranslation) * planeScalingMatrix;
		glm::mat4 planeMVP = m_Proj * m_View * planeModel;
		m_PlaneShader->Bind();
		m_PlaneShader->SetUniformMat4f("u_MVP", planeMVP);
		m_PlaneShader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		renderer.Draw(*m_PlaneVAO, *m_PlaneIndexBuffer, *m_PlaneShader);
	}

	void TestScenery::OnImGuiRender()
	{
		ImGui::SliderFloat("Distance", &m_Translation.z, 0.0f, 1000.0f);
		ImGui::SliderFloat("Scale", &m_ScaleFactor, 0.0f, 540.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Cube position: (%.3f, %.3f, %.3f)", m_Translation.x, m_Translation.y, m_Translation.z);
	}

}