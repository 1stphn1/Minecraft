#include "Player.hpp"
#include "Chunk.hpp"

void Player::GravityAcc()
{
    if (m_ShouldFall) {
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
        y_pos += m_YSpeed * Gla::Timer::DeltaTime();
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
    }

    // TODO: add static variables for x and z that store players block coords; if player moves from that block, only then calculate height. The current code calculates height needlessly a lot of times

    int height;
    for (height = CHUNK_HEIGHT - 1; height >= (int)PLAYER_HEIGHT; height--)
    {
        // LOG(height);
        // LOG("ChunkX: " << player.ChunkX() << " - ChunkZ: " << player.ChunkZ());
        // LOG("X: " << (int)(player.GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(player.GetZ()) % CHUNK_LENGHT);

        if (Chunk::chunks[player.ChunkX()][player.ChunkZ()] == nullptr) {
            throw std::logic_error("Trying to dereference null from Player::GravityAcc()");
        }

        // if (y_pos - height > PLAYER_HEIGHT) {
        //     break;
        // }

        if (Chunk::chunks[player.ChunkX()][player.ChunkZ()]->GetBlockType( player.BlockX(), height, player.BlockZ() ) != BlockType::NO_BLOCK)
        {
            // LOG("X: " << (int)(player.GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(player.GetZ()) % CHUNK_LENGHT);
            break;
        }
    }

    // Adds 1 because the height of the top layer of a block is always exactly for 1.0 greater than its index
    if (y_pos - (height + 1) <= PLAYER_HEIGHT) {
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
    int x = player.BlockX();
    int y = player.BlockY();
    int z = player.BlockZ();

    if (x - 1 < 0 || x + 1 >= CHUNK_LENGHT)
    {
        LOG("Goes through X!");
        x_pos += value_to_add;
        return;
    }

    #ifdef GLA_DEBUG
        if (z < 0 || z >= CHUNK_LENGHT)
        {
            throw std::logic_error("z is out of bounds in Player::UpdateX()");
        }
    #endif

    if (value_to_add < 0.0f)
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x - 1, y - 1, z) == NO_BLOCK ||
            std::abs( x_pos - (float)(ChunkX() * CHUNK_LENGHT + player.BlockX()) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            x_pos += value_to_add;
        }
    }
    else
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x + 1, y - 1, z) == NO_BLOCK ||
            std::abs( x_pos - (float)(ChunkX() * CHUNK_LENGHT + player.BlockX() + 1) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            x_pos += value_to_add;
        }
    }
}

void Player::UpdateZ(float value_to_add)
{
    int x = player.BlockX();
    int y = player.BlockY();
    int z = player.BlockZ();

    if (z - 1 < 0 || z + 1 >= CHUNK_LENGHT)
    {
        LOG("Goes through Z!");
        z_pos += value_to_add;
        return;
    }

    #ifdef GLA_DEBUG
        if (x < 0 || x >= CHUNK_LENGHT)
        {
            throw std::logic_error("z is out of bounds in Player::UpdateX()");
        }
    #endif

    if (value_to_add < 0.0f)
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x, y - 1, z - 1) == NO_BLOCK ||
            std::abs(z_pos - (float)(ChunkZ() * CHUNK_LENGHT + player.BlockZ()) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            z_pos += value_to_add;
        }
    }
    else
    {
        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x, y - 1, z + 1) == NO_BLOCK ||
            std::abs(z_pos - (float)(ChunkZ() * CHUNK_LENGHT + player.BlockZ() + 1) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            z_pos += value_to_add;
        }
    }
}