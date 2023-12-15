#pragma once

#include <vector>
#include <bitset>
#include <unordered_map>

#include "Definitions.h"
#include "Gla/Shader.h"
#include "Player.h"

enum BlockType {
    NO_BLOCK,
    GRASS_BLOCK,
    DIRT_BLOCK,
    TREE_LOG,
    STONE_BLOCK,
    SAND_BLOCK,
    LEAVE_BLOCK,
    WATER
};

class Block
{
public:
    static constexpr bool IsTransparent(BlockType block)
    {
        // Transparent block start from LEAVE_BLOCK in the BlockType enum
        if (block >= LEAVE_BLOCK) {
            return true;
        }

        return false;
    }

    static constexpr bool IsTransparentOrNoBlock(BlockType block)
    {
        if (block == NO_BLOCK || block >= LEAVE_BLOCK) {
            return true;
        }

        return false;
    }

    static constexpr float GetBlockShaderValue(BlockType block_type)
    {
        // constexpr float GRASS_BLOCK_VALUE = 10.0f;
        // constexpr float DIRT_BLOCK_VALUE  = 20.0f;
        // constexpr float TREE_LOG_VALUE    = 30.0f;
        // constexpr float LEAVE_BLOCK_VALUE = 40.0f;
        // constexpr float WATER_BLOCK_VALUE = 50.0F;

        // switch (block_type) {
        //     case BlockType::GRASS_BLOCK:
        //         return GRASS_BLOCK_VALUE;
        //     case BlockType::DIRT_BLOCK:
        //         return DIRT_BLOCK_VALUE;
        //     case BlockType::TREE_LOG:
        //         return TREE_LOG_VALUE;
        //     case BlockType::LEAVE_BLOCK:
        //         return LEAVE_BLOCK_VALUE;
        //     case BlockType::WATER:
        //         return WATER_BLOCK_VALUE;
        //     default:
        //         return GRASS_BLOCK_VALUE;
        // }

        return block_type * 10.0f;
    }
};

class Chunk
{
public:
    enum Biome { OAK_FOREST };

    using ChunkData = Chunk *(*)[CHUNKS_ACROSS_X_AXIS];

    Chunk(int x, int z)
        : m_xCoord(x), m_zCoord(z)
    {
        ChooseBiome();
        GenerateChunk();
    }

    ~Chunk() = default;

    constexpr int GetX() const { return m_xCoord; }
    constexpr int GetZ() const { return m_zCoord; } 

    constexpr BlockType GetBlockType(int x, int y, int z) const
    {
        #ifdef GLA_DEBUG
            if (x >= CHUNK_LENGHT || y >= CHUNK_HEIGHT || z >= CHUNK_LENGHT || x < 0 || y < 0 || z < 0) {
                throw std::logic_error("coordinates out of bounds (X: " + std::to_string(x) + " - Y: " + std::to_string(y) + " - Z: " + std::to_string(z) + ") in Chunk::GetBlockType");
            }
        #endif

        return m_Blocks[y][z][x];
    }

    constexpr const BlockType (*Data() const)[CHUNK_LENGHT][CHUNK_LENGHT] { return m_Blocks; }

    constexpr std::vector<float>& GetNonTransparentVec() { return nontransparent_vertices; }
    constexpr std::vector<float>& GetTransparentVec()    { return transparent_vertices; }
    constexpr bool ShouldBeEmplaced() const { return emplaced; }    

    void EmplaceVertices();
    void FreeVertexData();
    void BreakBlock(Player& player);
    void PutBlock();

    static void FreeChunkData();
    // static void FreeUnneededVertexData();  // Should be called every frame in main()

    // Pointer to the chunk data
    static ChunkData chunks;

    bool emplaced = false;

private:
    void ChooseBiome();
    void GenerateChunk();
    
    inline int    BiomeOctaveValue() const          { return s_BiomeVals[m_Biome].OctaveVal; }
    inline double BiomePersistenceValue() const     { return s_BiomeVals[m_Biome].PersistenceVal;}
    inline int    BiomeTreeGenerationChance() const { return s_BiomeVals[m_Biome].TreeGenerationChanceVal;}

    int m_xCoord, m_zCoord;    // Chunk coordinates
    // std::array<blocks_t, CHUNK_HEIGHT * CHUNK_LENGHT * CHUNK_LENGHT> m_Blocks;  // Array of blocks in the chunk
    // blocks_t m_Blocks[CHUNK_HEIGHT * CHUNK_LENGHT * CHUNK_LENGHT];  // Array of blocks in the chunk
    // std::array<blocks_t, CHUNK_HEIGHT * CHUNK_LENGHT * CHUNK_LENGHT> m_Blocks;
    BlockType m_Blocks[CHUNK_HEIGHT][CHUNK_LENGHT][CHUNK_LENGHT];

    Biome m_Biome;

    std::vector<float> nontransparent_vertices;
    std::vector<float> transparent_vertices;

    struct BiomeValues {
        double PersistenceVal;
        int OctaveVal;
        int TreeGenerationChanceVal;
    };

    inline static std::unordered_map<Biome, BiomeValues> s_BiomeVals = {
        { Biome::OAK_FOREST, { 0.9, 7, 30 } }
    };
// public:  //!!
//     inline static std::vector<ChunkCoord> s_LoadedChunks;  // Chunks with saved vertex data
};

constexpr float cube_vertices[] = {
    //   cube coords    texture coords   face //
    /*front face*/
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   0.0f,  // bottom-left  0
    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,   0.0f,  // bottom-right 1
    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f,  // top-right    2
    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f,  // top-right    2
    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f,  // top-left     3
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   0.0f,  // bottom-left  0

    /*back face*/
    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   1.0f,  // top-right    6
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   1.0f,  // top-left     7
    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   1.0f,  // bottom-left  4
    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   1.0f,  // bottom-left  4
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   1.0f,  // bottom-right 5
    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   1.0f,  // top-right    6

    /*left face*/
    0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   2.0f,  // top-left     7
    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   2.0f,  // bottom-left  4
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   2.0f,  // bottom-left  0
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   2.0f,  // bottom-left  0
    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,   2.0f,  // top-left     3
    0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   2.0f,  // top-left     7

    /*right face*/
    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   3.0f,  // top-right    6
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   3.0f,  // bottom-right 5
    1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   3.0f,  // bottom-right 1
    1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   3.0f,  // bottom-right 1
    1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   3.0f,  // top-right    2
    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,   3.0f,  // top-right    6

    /*top face*/
    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,   4.0f,  // top-left     3
    1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   4.0f,  // top-right    2
    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   4.0f,  // top-right    6
    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   4.0f,  // top-right    6
    0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   4.0f,  // top-left     7
    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,   4.0f,  // top-left     3

    /*bottom face*/
    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   5.0f,  // bottom-left  0
    1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   5.0f,  // bottom-right 1
    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   5.0f,  // bottom-right 5
    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   5.0f,  // bottom-right 5
    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   5.0f,  // bottom-left  4
    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   5.0f,  // bottom-left  0
};

constexpr int CUBE_VB_ELEMENTS_COUNT = sizeof(cube_vertices) / sizeof(float);  // Count of elements in cube_vertices vertex buffer (or VB)
constexpr int FACE_ELEMENTS_COUNT    = CUBE_VB_ELEMENTS_COUNT / 6;
constexpr int VERTICES_PER_FACE      = 6;
constexpr int ELEMENTS_PER_VERTEX    = FACE_ELEMENTS_COUNT / VERTICES_PER_FACE;