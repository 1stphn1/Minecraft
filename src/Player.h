#pragma once

#include "Definitions.h"
#include "Gla/UniformBuffer.h"
#include "Gla/Timer.h"

class Player
{
public:
    Player()
        : x_pos(CHUNKS_ACROSS_X_AXIS / 2 * CHUNK_LENGHT),
          y_pos(CHUNK_HEIGHT),
          z_pos(CHUNKS_ACROSS_Z_AXIS / 2 * CHUNK_LENGHT),
          xz_angle(0.0f),
          y_angle(0.0f),
          move_dist(BASE_MOVE_DIST),
          m_UniformBuffer(nullptr),
          m_ViewMtr(glm::translate(glm::mat4(1.0f), glm::vec3(x_pos, y_pos, z_pos))) {}

    constexpr void SetUniformBuffer(Gla::UniformBuffer& u_buffer)
    {
        m_UniformBuffer = &u_buffer;
    }

    inline void updateView()
    {
        m_ViewMtr = glm::rotate(glm::mat4(1.0f), glm::radians(y_angle), x_axis) * glm::rotate(glm::mat4(1.0f), glm::radians(xz_angle), y_axis)
        * glm::translate(glm::mat4(1.0f), glm::vec3(-x_pos, -y_pos, -z_pos));
        m_UniformBuffer->UpdateData((void*)&(PROJECTION_MTR * m_ViewMtr)[0][0]);
    }

    inline void changeSpeed()
    {
        static unsigned int multiplier = 1;

        move_dist = BASE_MOVE_DIST * multiplier;

        multiplier += 6;

        if (multiplier >= 25) {
            multiplier = 1;
        }
    }

    void GravityAcc();
    void Jump();
    void UpdateX(float value_to_add);
    void UpdateY(float value_to_add);
    void Update();  // Runs every frame

    float x_pos;
    float y_pos;
    float z_pos;

    float xz_angle;
    float y_angle;

    constexpr int ChunkX() const { return (int)x_pos / CHUNK_LENGHT; }
    constexpr int ChunkZ() const { return (int)z_pos / CHUNK_LENGHT; }

    constexpr float GetX() const { return x_pos; }
    constexpr float GetY() const { return y_pos; }
    constexpr float GetZ() const { return z_pos; }

    constexpr float GetXZangle() const { return xz_angle; }
    constexpr float GetYangle()  const { return y_angle; }

    constexpr float GetMoveDist()  const { return move_dist; }
    constexpr float GetMoveAngle() const { return BASE_MOVE_ANGLE; }

    constexpr glm::mat4 GetViewMtr() const { return m_ViewMtr; }

private:
    glm::mat4 m_ViewMtr;
    Gla::UniformBuffer* m_UniformBuffer;

    float move_dist;
    float m_YSpeed = 0.0f;

    bool m_ShouldFall = true;

    static constexpr float GravityAcceleration = 9.81f;
    static constexpr float BASE_MOVE_DIST = 0.06f;
    static constexpr float BASE_MOVE_ANGLE = 2.4f;
    static constexpr float PLAYER_HEIGHT = 2.0f;
};

inline Player player;