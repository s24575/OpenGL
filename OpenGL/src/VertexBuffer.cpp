#include "VertexBuffer.h"

#include "DebugUtil.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RednererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RednererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RednererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RednererID));
}

void VertexBuffer::Unbind() const
{

}