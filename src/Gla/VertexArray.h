#pragma once

#include "GlaBase.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Gla
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;

    private:
        unsigned int m_RendererID;
    };
}