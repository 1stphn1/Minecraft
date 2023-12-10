#include "Player.h"
#include "Chunk.h"

void Player::GravityAcc()
{
    if (m_ShouldFall) {
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
        y_pos += m_YSpeed * Gla::Timer::DeltaTime();
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
    }

    int height;
    for (height = CHUNK_HEIGHT - 1; height >= (int)PLAYER_HEIGHT; height--)
    {
        // LOG(height);
        // LOG("ChunkX: " << player.ChunkX() << " - ChunkZ: " << player.ChunkZ());
        // LOG("X: " << (int)(player.GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(player.GetZ()) % CHUNK_LENGHT);

        if (Chunk::chunks[player.ChunkX()][player.ChunkZ()] == nullptr) {
            throw std::logic_error("Trying to dereference null from Player::GravityAcc()");
        }

        if (y_pos - height > PLAYER_HEIGHT) {
            break;
        }

        if (Chunk::chunks[player.ChunkX()][player.ChunkZ()]->GetBlockType( (int)(player.GetX() + 0.5f) % CHUNK_LENGHT, height, (int)(player.GetZ() + 0.5f) % CHUNK_LENGHT ) != BlockType::NO_BLOCK)
        {
            // LOG("X: " << (int)(player.GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(player.GetZ()) % CHUNK_LENGHT);
            break;
        }
    }

    if (y_pos - height <= PLAYER_HEIGHT) {
        m_YSpeed = 0.0f;
        m_ShouldFall = false;
        return;
    } else {
        m_ShouldFall = true;
    }
}

void Player::Jump()
{
    if (m_ShouldFall) {
        return;
    }

    m_YSpeed += 5.0f;
    m_ShouldFall = true;
}

void Player::UpdateX(float value_to_add)
{
    if ((int)(x_pos) % CHUNK_LENGHT - 1 < 0 || (int)(x_pos) % CHUNK_LENGHT + 1 >= CHUNK_LENGHT) {
        x_pos += value_to_add;
        return;
    }

    if (value_to_add < 0.0f)
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(
           (int)(x_pos) % CHUNK_LENGHT - 1, (int)(y_pos - PLAYER_HEIGHT + 0.7f), (int)(z_pos) % CHUNK_LENGHT ) == NO_BLOCK
           || std::abs(x_pos - ( (float)(ChunkX() * CHUNK_LENGHT + (int)(x_pos) % CHUNK_LENGHT - 1) + 0.5f )) >= 0.07f)
        {
            x_pos += value_to_add;
        }
    }
    else
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(
           (int)(x_pos) % CHUNK_LENGHT + 1, (int)(y_pos/* - PLAYER_HEIGHT + 0.7f*/), (int)(z_pos) % CHUNK_LENGHT ) == NO_BLOCK
           || std::abs(x_pos - ( (float)(ChunkX() * CHUNK_LENGHT + (int)(x_pos) % CHUNK_LENGHT + 1) - 0.5f )) >= 0.07f)
        {
            x_pos += value_to_add;
        }
    }
}

void Player::UpdateY(float value_to_add)
{

}