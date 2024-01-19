#include "Player.hpp"
#include "Chunk.hpp"

void Player::GravityAcc()
{
    if (!m_DoGravity)
    {
        return;
    }
    
    if (m_ShouldFall)
    {
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
        y_pos += m_YSpeed * Gla::Timer::DeltaTime();
        m_YSpeed -= GravityAcceleration * Gla::Timer::DeltaTime() * 0.5f;
    }

    // TODO: add static variables for x and z that store players block coords; if player moves from that block, only then calculate height. The current code calculates height needlessly a lot of times

    int height;
    for (height = CHUNK_HEIGHT - 1; height >= (int)PLAYER_HEIGHT; height--)
    {
        // LOG(height);
        // LOG("ChunkX: " << ChunkX() << " - ChunkZ: " << ChunkZ());
        // LOG("X: " << (int)(GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(GetZ()) % CHUNK_LENGHT);

        if (Chunk::chunks[ChunkX()][ChunkZ()] == nullptr) {
            throw std::logic_error("Trying to dereference null from Player::GravityAcc()");
        }

        // if (y_pos - height > PLAYER_HEIGHT) {
        //     break;
        // }

        if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType( BlockX(), height, BlockZ() ) != BlockType::NO_BLOCK)
        {
            // LOG("X: " << (int)(GetX()) % CHUNK_LENGHT << " - Y: " << height << " - Z: " << (int)(GetZ()) % CHUNK_LENGHT);
            break;
        }
    }

    // Adds 1 because the height of the top layer of a block is always exactly for 1.0 greater than its index
    if (y_pos - (height + 1) <= PLAYER_HEIGHT)
    {
        m_YSpeed = 0.0f;
        m_ShouldFall = false;
        return;
    }
    else
    {
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
    int x = BlockX();
    int y = BlockY();
    int z = BlockZ();
    int chunk_x_index = ChunkX();

    // if (x - 1 < 0 || x + 1 >= CHUNK_LENGHT)
    // {
    //     LOG("Goes through x!");
    // }

    if (value_to_add < 0.0f)
    {
        int xcoord_to_check = x - 1;  // left from x

        if (xcoord_to_check < 0)
        {
            chunk_x_index--;
            xcoord_to_check = CHUNK_LENGHT - 1;
        }
        
        if (Chunk::chunks[chunk_x_index][ChunkZ()]->GetBlockType(xcoord_to_check, y - 1, z) == NO_BLOCK ||
            std::abs( x_pos - (float)(chunk_x_index * CHUNK_LENGHT + (xcoord_to_check % CHUNK_LENGHT) + 1) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            x_pos += value_to_add;
        }
    }
    else
    {
        int xcoord_to_check = x + 1;  // right from x
        
        if (xcoord_to_check >= CHUNK_LENGHT)
        {
            chunk_x_index++;
            xcoord_to_check = 0;
        }
        
        if (Chunk::chunks[chunk_x_index][ChunkZ()]->GetBlockType(xcoord_to_check, y - 1, z) == NO_BLOCK ||
            std::abs( x_pos - (float)(chunk_x_index * CHUNK_LENGHT + (xcoord_to_check % CHUNK_LENGHT)) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            x_pos += value_to_add;
        }
    }
}

void Player::UpdateZ(float value_to_add)
{  
    const int x = BlockX();
    const int y = BlockY();
    const int z = BlockZ();
    int chunk_z_index = ChunkZ();

    // if (z - 1 < 0 || z + 1 >= CHUNK_LENGHT)
    // {
    //     LOG("Goes through z!");
    // }

    if (value_to_add < 0.0f)
    {
        int zcoord_to_check = z - 1;  // Block in front of current player's z coord

        if (zcoord_to_check < 0)  // If the block coordinate is lesser than 0, that means the block to check is in the neighbouring chunk
        {
            chunk_z_index--;
            zcoord_to_check = CHUNK_LENGHT - 1;
        }
        
        if (Chunk::chunks[ChunkX()][chunk_z_index]->GetBlockType(x, y - 1, zcoord_to_check) == NO_BLOCK ||
            std::abs( z_pos - (float)(chunk_z_index * CHUNK_LENGHT + (zcoord_to_check % CHUNK_LENGHT) + 1) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            z_pos += value_to_add;
        }
    }
    else
    {
        int zcoord_to_check = z + 1;  // Block behind current player's z coord
        
        if (zcoord_to_check >= CHUNK_LENGHT) // If the block coordinate is greater than CHUNK_LENGHT, that means the block to check is in the neighbouring chunk
        {
            chunk_z_index++;
            zcoord_to_check = 0;
        }
        
        if (Chunk::chunks[ChunkX()][chunk_z_index]->GetBlockType(x, y - 1, zcoord_to_check) == NO_BLOCK ||
            std::abs( z_pos - (float)(chunk_z_index * CHUNK_LENGHT + (zcoord_to_check % CHUNK_LENGHT)) ) >= MIN_DISTANCE_FROM_BLOCK)
        {
            z_pos += value_to_add;
        }
    }

    
    // int x = BlockX();
    // int y = BlockY();
    // int z = BlockZ();

    // if (z - 1 < 0 || z + 1 >= CHUNK_LENGHT)
    // {
    //     LOG("Goes through Z!");
    //     z_pos += value_to_add;
    //     return;
    // }

    // #ifdef GLA_DEBUG
    //     if (x < 0 || x >= CHUNK_LENGHT)
    //     {
    //         throw std::logic_error("z is out of bounds in Player::UpdateX()");
    //     }
    // #endif

    // if (value_to_add < 0.0f)
    // {
    //     if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x, y - 1, z - 1) == NO_BLOCK ||
    //         std::abs(z_pos - (float)(ChunkZ() * CHUNK_LENGHT + BlockZ()) ) >= MIN_DISTANCE_FROM_BLOCK)
    //     {
    //         z_pos += value_to_add;
    //     }
    // }
    // else
    // {
    //     if (Chunk::chunks[ChunkX()][ChunkZ()]->GetBlockType(x, y - 1, z + 1) == NO_BLOCK ||
    //         std::abs(z_pos - (float)(ChunkZ() * CHUNK_LENGHT + BlockZ() + 1) ) >= MIN_DISTANCE_FROM_BLOCK)
    //     {
    //         z_pos += value_to_add;
    //     }
    // }
}