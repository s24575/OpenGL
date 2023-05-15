#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <shapes/Cube.h>

#include <memory>

namespace test {

	class TestRotation : public Test
	{
	public:
		TestRotation();
		~TestRotation();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;

		Cube m_Cube;
		float m_ScaleFactor;

		double m_CurrentTime;
	};

}