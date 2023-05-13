#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "shapes/Cube.h"
#include "shapes/Plane.h"

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& vb, const Shader& shader) const;
	void Draw(const Cube& cube) const;
	void Draw(const Plane& plane) const;
};