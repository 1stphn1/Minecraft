#pragma once

#include "Definitions.hpp"
#include "Gla/UniformBuffer.hpp"
#include "Gla/Timer.hpp"

constexpr int PLAYER_DEFAULT_X = CHUNKS_ACROSS_X_AXIS / 2 * CHUNK_LENGHT;
constexpr int PLAYER_DEFAULT_Y = CHUNK_HEIGHT; 
constexpr int PLAYER_DEFAULT_Z = CHUNKS_ACROSS_Z_AXIS / 2 * CHUNK_LENGHT;

class Player
{
public:
    Player()
        : x_pos(PLAYER_DEFAULT_X),
          y_pos(PLAYER_DEFAULT_Y),
          z_pos(PLAYER_DEFAULT_Z),
          xz_angle(0.0f),
          y_angle(0.0f),
          move_dist(BASE_MOVE_DIST),
          m_UniformBuffer(nullptr),
          m_ViewMtr(glm::translate(glm::mat4(1.0f), glm::vec3(x_pos, y_pos, z_pos))) {}

    constexpr void SetUniformBuffer(Gla::UniformBuffer& u_buffer)
    {
        m_UniformBuffer = &u_buffer;
    }

    inline void UpdateView()
    {
        m_ViewMtr = glm::rotate(glm::mat4(1.0f), glm::radians(y_angle), x_axis) * glm::rotate(glm::mat4(1.0f), glm::radians(xz_angle), y_axis)
        * glm::translate(glm::mat4(1.0f), glm::vec3(-x_pos, -y_pos, -z_pos));
        m_UniformBuffer->UpdateData((void*)&(PROJECTION_MTR * m_ViewMtr)[0][0]);
    }

    inline void ChangeSpeed()
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
    void UpdateZ(float value_to_add);
    void Update();  // Runs every frame

    float x_pos;
    float y_pos;
    float z_pos;

    float xz_angle;
    float y_angle;

    // These are the coordinates of the chunk where the player is located
    constexpr int ChunkX() const { return (int)x_pos / CHUNK_LENGHT; }
    constexpr int ChunkZ() const { return (int)z_pos / CHUNK_LENGHT; }

    constexpr float GetX() const { return x_pos; }
    constexpr float GetY() const { return y_pos; }
    constexpr float GetZ() const { return z_pos; }

    // Coordinates of the block of player's camera
    constexpr int BlockX() const { return (int)x_pos % CHUNK_LENGHT; }
    constexpr int BlockY() const { return (int)y_pos; }
    constexpr int BlockZ() const { return (int)z_pos % CHUNK_LENGHT; }

    // Camera angles
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
    static constexpr float PLAYER_HEIGHT = 1.85f;
    static constexpr float MIN_DISTANCE_FROM_BLOCK = 0.099f;
};

inline Player player;