#include "Chunk.h"
#include "Noise.h"

#include <random>

// Will be set to the singleton 'class Player' variable in main function.
Chunk::ChunkData Chunk::chunks = new Chunk*[CHUNKS_ACROSS_Z_AXIS][CHUNKS_ACROSS_X_AXIS]();

void Chunk::ChooseBiome()
{
    m_Biome = Biome::OAK_FOREST;
}

void Chunk::GenerateChunk()
{
    for (int y = 0; y < CHUNK_HEIGHT; y++)
    {
        for (int z = 0; z < CHUNK_LENGHT; z++)
        {
            for (int x = 0; x < CHUNK_LENGHT; x++)
            {
                m_Blocks[y][z][x] = BlockType::NO_BLOCK;
            }
        }   
    }

    static std::uniform_int_distribution dist(0, BiomeTreeGenerationChance());
    static std::random_device rd;
    static const int tree_generation_chance = BiomeTreeGenerationChance();

    const int smoothness = CHUNK_HEIGHT * 2 * 2;

    for (int z_coord = CHUNK_LENGHT - 1; z_coord >= 0; --z_coord)
    {
        for (int x_coord = CHUNK_LENGHT - 1; x_coord >= 0; --x_coord)
        {
            double f_x = (double)(x_coord + this->m_xCoord * CHUNK_LENGHT) / smoothness;
            double f_z = (double)(z_coord + this->m_zCoord * CHUNK_LENGHT) / smoothness;

            double noise_val = noise::fractal_perlin_noise(f_x, f_z, BiomeOctaveValue(), BiomePersistenceValue());
            int height = (int)(noise_val * CHUNK_HEIGHT / 2 + CHUNK_HEIGHT / 2);
            // LOG(noise);

            if (height >= CHUNK_HEIGHT) {
                height = CHUNK_HEIGHT - 1;
            } else if (height < 0) {
                height = 0;
            }

            int tree_height = 0;

            // If tree height (height + 6) won't be out of the height limit && if one in 256
            if (height + 6 < CHUNK_HEIGHT && height > WATER_LEVEL && dist(rd) == tree_generation_chance) {
                tree_height = height + 5;

                for (int tree_z = z_coord - 1; tree_z <= z_coord + 1; tree_z++)
                {
                    for (int tree_x = x_coord - 1; tree_x <= x_coord + 1; tree_x++)
                    {   
                        for (int tree_y = tree_height - 1; tree_y <= tree_height + 1; tree_y++)
                        {
                            // If out of chunk bounds
                            if (tree_z < 0 || tree_z >= CHUNK_LENGHT - 1 || tree_x < 0 || tree_x >= CHUNK_LENGHT - 1 || tree_y < 0 || tree_y >= CHUNK_HEIGHT - 1) {
                                continue;
                            }

                            if (tree_y == tree_height + 1 && (  // If at angles on the top leave layer, then no leave blocks
                               (tree_z == z_coord - 1 && tree_x == x_coord - 1) || (tree_z == z_coord - 1 && tree_x == x_coord + 1) ||
                               (tree_z == z_coord + 1 && tree_x == x_coord - 1) || (tree_z == z_coord + 1 && tree_x == x_coord + 1) ))
                            {
                                continue;
                            }
                            
                            // m_Blocks[tree_y * CHUNK_LENGHT * CHUNK_LENGHT + tree_z * CHUNK_LENGHT + tree_x] = BlockType::LEAVE_BLOCK;
                            m_Blocks[tree_y][tree_z][tree_x] = BlockType::LEAVE_BLOCK;
                        }
                    }
                }
            }

            for (int y_coord = CHUNK_HEIGHT - 1; y_coord >= 0; y_coord--)
            {
                // If between tree height && terrani height at the given x and z coordinates, then set block to be tree log
                if (y_coord <= tree_height && y_coord > height)
                {
                    m_Blocks[y_coord][z_coord][x_coord] = BlockType::TREE_LOG;
                }
                else if (y_coord > height)  // If greater than terrain height and no tree
                {
                    // Leave blocks don't generate at given x and z coords only, so have to check if there's a leave block
                    if (m_Blocks[y_coord][z_coord][x_coord] != BlockType::LEAVE_BLOCK) {
                        m_Blocks[y_coord][z_coord][x_coord]  = BlockType::NO_BLOCK;
                    }
                }
                else if (y_coord == height)  // Top terrain blocks should be grass
                {
                    m_Blocks[y_coord][z_coord][x_coord] = BlockType::GRASS_BLOCK;
                }
                else if (y_coord >= height - 5) // Below top layer is dirt
                {
                    m_Blocks[y_coord][z_coord][x_coord] = BlockType::DIRT_BLOCK;
                }
                else
                {
                    m_Blocks[y_coord][z_coord][x_coord] = BlockType::STONE_BLOCK;
                }
            }

            for (int i = WATER_LEVEL; i > height; i--) {
                m_Blocks[i][z_coord][x_coord] = BlockType::WATER;
            }

            if (height <= WATER_LEVEL + 1) {
                m_Blocks[height][z_coord][x_coord] = BlockType::SAND_BLOCK;

                if (height >= 2) {
                    m_Blocks[height - 1][z_coord][x_coord] = BlockType::SAND_BLOCK;
                    m_Blocks[height - 2][z_coord][x_coord] = BlockType::SAND_BLOCK;
                }
            }
        }
    }
}

void Chunk::BreakBlock(Player& player)
{
    int x = 0, y = 0, z = 0;

    // Angles of player's looking direction
    float player_xz_sin =  glm::sin(glm::radians(player.GetXZangle()));
    float player_xz_cos = -glm::cos(glm::radians(player.GetXZangle()));
    float player_y_sin  = -glm::sin(glm::radians(player.GetYangle()));
    float player_y_cos  =  glm::cos(glm::radians(player.GetYangle()));

    if (player.GetYangle() > 0.0f) {
        player_y_cos *= -1.0f;
    }

    // Index of the chunk from which a block will be destroyed
    int chunk_x_index, chunk_z_index;

    for (float ray = 0.0f; ray <= 8.0f; ray += 0.05f)  // Shooting a ray from camera to check wether there's a block
    {
        x = (int)(ray * player_xz_sin) + (int)(player.GetX() + 0.5f) - player.ChunkX() * CHUNK_LENGHT;
        z = (int)(ray * player_xz_cos) + (int)(player.GetZ() + 0.5f) - player.ChunkZ() * CHUNK_LENGHT;

        float h = player_y_sin * ray / player_y_cos;
        y = (int)(player_y_sin * h) + (int)(player.GetY() + 0.5f);

        // y = (int)(glm::tan(player.GetYangle()) * ray) + (int)(player.GetY() + 0.5f);

        // Checks if a block from a surrounding chunk should be destroyed (that is, if selected block is from a surrounding chunk)
        chunk_x_index = m_xCoord;
        chunk_z_index = m_zCoord;

        if (z < 0)  // The if-else statements below check if the x and y coordinates are out of bounds (in other words, if the block is from a surrounding chunk)
        {
            chunk_z_index = m_zCoord - 1;
            z += CHUNK_LENGHT;
        }
        else if (z > CHUNK_LENGHT - 1)
        {
            chunk_z_index = m_zCoord + 1;
            z -= CHUNK_LENGHT;
        }

        if (x < 0)
        {
            chunk_x_index = m_xCoord - 1;
            x += CHUNK_LENGHT;
        }
        else if (x > CHUNK_LENGHT - 1)
        {
            chunk_x_index = m_xCoord + 1;
            x -= CHUNK_LENGHT;
        }

        // If the block is found (i.e. not 'NO_BLOCK') then break out of the loop and break the block
        if (Chunk::chunks[chunk_x_index][chunk_z_index]->m_Blocks[y][z][x] != NO_BLOCK) {
            break;
        }
    }

    // LOG("Y: " << y);
    
    if (x < 0 || y < 0 || z < 0 || x >= CHUNK_LENGHT || y >= CHUNK_HEIGHT || z >= CHUNK_LENGHT) {
        #ifdef GLA_DEBUG
            LOG("coordinates out of bounds ( range [0..16) ) in Chunk::BreakBlock");
        #endif

        return;
    }

    if (Chunk::chunks[chunk_x_index][chunk_z_index]->m_Blocks[y][z][x] != WATER) {
        Chunk::chunks[chunk_x_index][chunk_z_index]->m_Blocks[y][z][x] = NO_BLOCK;
    }

    FreeVertexData();
}

void Chunk::EmplaceVertices()
{
    if (emplaced) {
        return;
    }

    enum Faces {
        FRONT_FACE,
        BACK_FACE,
        LEFT_FACE,
        RIGHT_FACE,
        TOP_FACE,
        BOTTOM_FACE
    };

    const auto& chunk       = *Chunk::chunks[m_xCoord][m_zCoord];
    const auto& left_chunk  = *Chunk::chunks[m_xCoord - 1][m_zCoord];
    const auto& right_chunk = *Chunk::chunks[m_xCoord + 1][m_zCoord];
    const auto& front_chunk = *Chunk::chunks[m_xCoord][m_zCoord + 1];
    const auto& back_chunk  = *Chunk::chunks[m_xCoord][m_zCoord - 1];

    enum Indexes { X, Y, Z };  // Additional vertex data indices
    float additional_vertex_data[ELEMENTS_PER_VERTEX] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    const auto chunk_blocks  = chunk.Data();
    const auto lchunk_blocks = left_chunk.Data();
    const auto rchunk_blocks = right_chunk.Data();
    const auto fchunk_blocks = front_chunk.Data();
    const auto bchunk_blocks = back_chunk.Data();

    for (int block_y = CHUNK_HEIGHT - 1; block_y >= 0; block_y--)
    {
        for (int block_z = CHUNK_LENGHT - 1; block_z >= 0; block_z--)
        {
            for (int block_x = CHUNK_LENGHT - 1; block_x >= 0; block_x--)
            {
                if (chunk_blocks[block_y][block_z][block_x] == BlockType::NO_BLOCK) {
                    continue;
                }

                // std::vector<float>& vertices_container = nontrans_verts;

                additional_vertex_data[X] = float(block_x + m_xCoord * CHUNK_LENGHT);
                additional_vertex_data[Y] = float(block_y);
                additional_vertex_data[Z] = float(block_z + m_zCoord * CHUNK_LENGHT);
                additional_vertex_data[5] = Block::GetBlockShaderValue(chunk_blocks[block_y][block_z][block_x]);

                std::vector<float>& vertices_container = ( Block::IsTransparent(chunk_blocks[block_y][block_z][block_x] ) ? 
                transparent_vertices : nontransparent_vertices );

                if (chunk_blocks[block_y][block_z][block_x] == BlockType::WATER)
                {
                    int y = block_y;
                    for (; chunk_blocks[y][block_z][block_x] == BlockType::WATER; y++);
                    y--;

                    float float_y = y - 0.1f; 
                    additional_vertex_data[Y] = float_y;

                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }

                    continue;
                }

                if (Block::IsTransparent(chunk_blocks[block_y][block_z][block_x]))
                {
                    for (int i = 0; i < CUBE_VB_ELEMENTS_COUNT; i++)
                    {
                        vertices_container.emplace_back(cube_vertices[i] + additional_vertex_data[i % ELEMENTS_PER_VERTEX]);
                    }

                    continue;
                }

                // No need to add to texture coordinates and texture slots in the vertices_container array; that's the reason for adding 0-s

                if (  // if player is behind the front face, they can't see it
                   (block_z + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z + 1][block_x]) :  // if there is a block in front, then it's impossible to see front face
                    Block::IsTransparentOrNoBlock(fchunk_blocks[block_y][0][block_x])))  // if block_z is on the chunk's edge, checks the block in front from the chunk in front
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::FRONT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }

                if (  // if player is in front of the back face, they can't see it
                   (block_z - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z - 1][block_x]) :
                    Block::IsTransparentOrNoBlock(bchunk_blocks[block_y][CHUNK_LENGHT - 1][block_x])))
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::BACK_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }

                if (
                   (block_x - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x - 1]) :
                    Block::IsTransparentOrNoBlock(lchunk_blocks[block_y][block_z][CHUNK_LENGHT - 1])))
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::LEFT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }

                if (
                   (block_x + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x + 1]) :
                    Block::IsTransparentOrNoBlock(rchunk_blocks[block_y][block_z][0])))
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::RIGHT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }

                if (
                   (block_y + 1 >= CHUNK_HEIGHT || Block::IsTransparentOrNoBlock(chunk_blocks[block_y + 1][block_z][block_x])))
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }

                if (
                   (block_y - 1 < 0 || Block::IsTransparentOrNoBlock(chunk_blocks[block_y - 1][block_z][block_x])))
                {
                    for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
                        vertices_container.emplace_back(cube_vertices[Faces::BOTTOM_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
                    }
                }
            }
        }
    }

    emplaced = true;
    // s_LoadedChunks.push_back({ m_xCoord, m_zCoord });
}

void Chunk::FreeVertexData()
{   
    nontransparent_vertices.clear();
    transparent_vertices.clear();
    emplaced = false;
}

void Chunk::FreeChunkData()
{
    for (int i = 0; i < CHUNKS_ACROSS_Z_AXIS; i++)
        for (int j = 0; j < CHUNKS_ACROSS_X_AXIS; j++)
            if (chunks[i][j] != nullptr)
                delete chunks[i][j];

    delete[] chunks;
}

// void Chunk::FreeUnneededVertexData()
// {
    // static std::vector<std::vector<ChunkCoord>::iterator> elements_to_be_removed;  // Is static so memory wouldn't be allocated each time the function executes

    // for (auto it = s_LoadedChunks.begin(); it != s_LoadedChunks.end(); it++)
    // {
    //     if (std::abs((*it).x - player.ChunkX() > VIEW_DISTANCE) || std::abs((*it).z - player.ChunkZ() > VIEW_DISTANCE))  // Checks if coord are out of view distance
    //     {
    //         if (chunks[(*it).x][(*it).z] == nullptr) {
    //             throw std::logic_error("chunks[" + std::to_string((*it).x) + "][" + std::to_string((*it).z) + "] je null");
    //             continue;
    //         }

    //         elements_to_be_removed.push_back(it);
    //         chunks[(*it).x][(*it).z]->FreeVertexData();
    //     }
    // }

    // for (auto& it : elements_to_be_removed)
    // {
    //     s_LoadedChunks.erase(it);
    // }
// }
