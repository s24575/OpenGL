#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "shapes/Cube.h"
#include "shapes/Plane.h"

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
		glm::mat4 m_Proj, m_View;

		Cube m_Cube;
		float m_CubeScaleFactor;

		//Plane m_Plane;
		float m_PlaneScaleFactor;

		double m_CurrentTime;
	};

}