#pragma once

#include "GlaBase.h"

namespace Gla
{
    // This class is only suited for a uniform block with only one 4x4 matrix
    class UniformBuffer
    {
    public:
        UniformBuffer(const void* data = nullptr);
        ~UniformBuffer() = default;

        void UpdateData(const void* data);
        void Bind() const;

        constexpr const unsigned int GetHandle() const
        {
            return m_RendererID;
        }
        
    private:
        unsigned int m_RendererID;
        unsigned int m_Size;
        static constexpr unsigned int BlockSize = 16 * sizeof(float);

        char* m_BufferData;
    };
} // namespace Gla