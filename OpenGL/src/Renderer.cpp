#include "Renderer.h"

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Cube& cube) const
{
    GLCall(glDrawElements(GL_TRIANGLES, cube.getVerticesCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const Plane& plane) const
{
    GLCall(glDrawElements(GL_TRIANGLES, plane.getVerticesCount(), GL_UNSIGNED_INT, nullptr));
}