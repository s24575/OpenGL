#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <memory>

namespace test {

	class TestScenery : public Test
	{
	public:
		TestScenery();
		~TestScenery();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_Translation;

		float m_ScaleFactor;

		std::unique_ptr<Shader> m_PlaneShader;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVertexBuffer;
		std::unique_ptr<IndexBuffer> m_PlaneIndexBuffer;

		glm::vec3 m_PlaneTranslation;

		float m_PlaneScaleFactor;

		double m_CurrentTime;
	};

}