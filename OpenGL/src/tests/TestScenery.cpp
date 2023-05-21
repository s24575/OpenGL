#include "TestScenery.h"

#include "DebugUtil.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLFW/glfw3.h"

namespace test {

	TestScenery::TestScenery()
		: m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f))),
		//m_CubeScaleFactor(100.0f),
		m_PlaneScaleFactor(100.0f),
		m_CurrentTime(0.0f)
	{
		m_Cube.setTranslation(0, 0, -200);
		m_Plane.setTranslation(0, 0, -200);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_DEPTH_TEST))
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

		//Renderer renderer;

		//glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Cube.getScaleFactor()));
		//glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Cube.getTranslation()) * scalingMatrix;
		//glm::mat4 mvp = m_Proj * m_View * model;
		//Shader* cubeShader = m_Cube.getShader();
		//cubeShader->Bind();
		//cubeShader->SetUniformMat4f("u_MVP", mvp);
		//cubeShader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		//m_Cube.draw();
		//cubeShader->Unbind();
		m_Cube.update(m_View, m_Proj, (float)m_CurrentTime);
		m_Cube.draw();


		glm::mat4 planeScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_PlaneScaleFactor));
		glm::mat4 planeModel = glm::translate(glm::mat4(1.0f), m_Plane.getTranslation()) * planeScalingMatrix;
		glm::mat4 planeMVP = m_Proj * m_View * planeModel;
		Shader* planeShader = m_Plane.getShader();
		planeShader->Bind();
		planeShader->SetUniformMat4f("u_MVP", planeMVP);
		planeShader->SetUniform1f("u_Delta", (float)m_CurrentTime);
		m_Plane.draw();
		planeShader->Unbind();
	}

	void TestScenery::OnImGuiRender()
	{
		glm::vec3& cube_coords = m_Cube.getTranslation();
		ImGui::SliderFloat("Cube z:", &cube_coords.z, 0.0f, -1000.0f);
		ImGui::SliderFloat("Cube scale", &m_Cube.getScaleFactor(), 0.0f, 540.0f);
		ImGui::Text("Cube position: (%.3f, %.3f, %.3f)", cube_coords.x, cube_coords.y, cube_coords.z);

		glm::vec3& plane_coords = m_Plane.getTranslation();
		ImGui::SliderFloat("Plane z:", &plane_coords.z, 0.0f, -1000.0f);
		ImGui::SliderFloat("Plane scale", &m_PlaneScaleFactor, 0.0f, 540.0f);
		ImGui::Text("Plane position: (%.3f, %.3f, %.3f)", plane_coords.x, plane_coords.y, plane_coords.z);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}