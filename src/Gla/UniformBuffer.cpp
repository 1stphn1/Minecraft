#include "UniformBuffer.h"

namespace Gla
{
    UniformBuffer::UniformBuffer(const void* data /*= nullptr*/)
    {
        GLCall( glGenBuffers(1, &m_RendererID) );
        GLCall( glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID) );
        GLCall( glBufferData(GL_UNIFORM_BUFFER, BlockSize, data, GL_DYNAMIC_DRAW) );
    }

    void UniformBuffer::UpdateData(const void* data)
    {
        GLCall( glBufferData(GL_UNIFORM_BUFFER, BlockSize, data, GL_DYNAMIC_DRAW) );
    }

    void UniformBuffer::Bind() const
    {
        GLCall( glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_RendererID) );
    }
}