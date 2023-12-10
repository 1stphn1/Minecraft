
float only_vertices[] =  {
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // A 0
   -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, // D 3
    0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, // C 2
    0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, // C 2
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // B 1
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // A 0

   -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, // E 4
    0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, // F 5
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // G 6
   -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, // E 4
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // G 6
   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // H 7

   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // H 11
   -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // D 8
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // A 9
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // A 9
   -0.5f, -0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // E 10
   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // H 11

    0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // B 12
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // C 13
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // G 14
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // G 14
    0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // F 15
    0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // B 12

   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // A 16
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // B 17
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // F 18
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // F 18
   -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // E 19
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // A 16

    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // C 20
   -0.5f,  0.5f, -0.5f,   1.0f, 0.0f,   0.0f, // D 21
   -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // H 22
   -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, // H 22
    0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, // G 23
    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   0.0f, // C 20
};

float vertices[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // F 5
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // G 6
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 7

   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
   -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // B 12
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // C 13
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // G 14
    0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // F 15

   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 17
    0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // F 18
   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
    0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // C 20
   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
   -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // G 23
};

// index data
unsigned int indices[] = {
    // front and back
    0, 3, 2,
    2, 1, 0,
    4, 5, 6,
    6, 7 ,4,
    // left and right
    11, 8, 9,
    9, 10, 11,
    12, 13, 14,
    14, 15, 12,
    // bottom and top
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};



float vertices[] = {
    // vertex pos         // UVs     
    // front face
   -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  // E 4
    0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  // F 5
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // G 6
   -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,  // E 4
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // G 6
   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // H 7

    // back face
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // A 0
   -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  // D 3
    0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  // C 2
    0.5f,  0.5f, -0.5f,   1.0f, 1.0f,  // C 2
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // B 1
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // A 0

    // left face
   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // H 11
   -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // D 8
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // A 9
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // A 9
   -0.5f, -0.5f,  0.5f,   1.0f, 1.0f,  // E 10
   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // H 11

    // right face
    0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // B 12
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  // C 13
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // G 14
    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // G 14
    0.5f, -0.5f,  0.5f,   0.0f, 1.0f,  // F 15
    0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // B 12

    // top face
    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
   -0.5f,  0.5f, -0.5f,   1.0f, 0.0f,  // D 21
   -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // H 22
   -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  // H 22
    0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
    0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20

    // back face
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // A 16
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  // B 17
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f,  // F 18
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f,  // F 18
   -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,  // E 19
   -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  // A 16
};


const float skybox_vertices[] = {
    // front face
    -1.0f, -1.0f,  1.0f, // bottom-left  0
    1.0f, -1.0f,  1.0f, // bottom-right 1
    1.0f,  1.0f,  1.0f, // top-right    2
    -1.0f,  1.0f,  1.0f, // top-left     3
    // back face
    -1.0f, -1.0f, -1.0f, // bottom-left  4  
    1.0f, -1.0f, -1.0f, // bottom-right 5
    1.0f,  1.0f, -1.0f, // top-right    6
    -1.0f,  1.0f, -1.0f  // top-left     7
};

const unsigned char skybox_indices[6][6] = {
    { 0, 1, 2, 2, 3, 0 }, // front face
    { 4, 5, 6, 6, 7, 4 }, // back face
    { 0, 3, 7, 7, 4, 0 }, // left face
    { 1, 2, 6, 6, 5, 1 }, // right face
    { 3, 2, 6, 6, 7, 3 }, // top face
    { 0, 1, 5, 5, 4, 0 }  // bottom face
};


// vertices emplacing old main code

/*const auto& chunk = *chunks[i][j];
for (int block_y = CHUNK_HEIGHT - 1; block_y >= 0; block_y--)
{
    for (int block_z = CHUNK_LENGHT - 1; block_z >= 0; block_z--)
    {
        for (int block_x = CHUNK_LENGHT - 1; block_x >= 0; block_x--)
        {
            enum Indexes { X, Y, Z };
            float block_coords[6] = { float(block_x + i * CHUNK_LENGHT), float(block_y), float(block_z + j * CHUNK_LENGHT), 0, 0, 0 }; // I made the array so I could use modulus to add to x, y and z
            // Don't need to add to texture coordinates and texture slots in the vertices array; that's the reason for adding 0-s at the end

            if (chunk.CheckBlockType(block_x, block_y, block_z) == BlockType::NO_BLOCK)
                continue;

            if (Player::z_pos > block_coords[Z] + 0.5f &&
                (block_z + 1 < CHUNK_LENGHT ? chunk.CheckBlockType(block_x, block_y, block_z + 1) == BlockType::NO_BLOCK : chunks[i][j+1]->CheckBlockType(block_x, block_y, 0) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::FRONT_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }

            if (Player::z_pos < block_coords[Z] - 0.5f &&
                (block_z - 1 >= 0 ? chunk.CheckBlockType(block_x, block_y, block_z - 1) == BlockType::NO_BLOCK : chunks[i][j-1]->CheckBlockType(block_x, block_y, 15) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::BACK_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }

            if (Player::x_pos < block_coords[X] - 0.5f &&
                (block_x - 1 >= 0 ? chunk.CheckBlockType(block_x - 1, block_y, block_z) == BlockType::NO_BLOCK : chunks[i-1][j]->CheckBlockType(15, block_y, block_z) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::RIGHT_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }

            if (Player::x_pos > block_coords[X] + 0.5f &&
                (block_x + 1 < CHUNK_LENGHT ? chunk.CheckBlockType(block_x + 1, block_y, block_z) == BlockType::NO_BLOCK : chunks[i+1][j]->CheckBlockType(0, block_y, block_z) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::LEFT_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }

            if (Player::y_pos > block_coords[Y] + 0.5f &&
                (block_y + 1 >= CHUNK_LENGHT || chunk.CheckBlockType(block_x, block_y + 1, block_z) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }

            if (Player::y_pos < block_coords[Y] - 0.5f &&
                (block_y - 1 < 0 || chunk.CheckBlockType(block_x, block_y - 1, block_z) == BlockType::NO_BLOCK))
            {
                for (int k = 0; k < FACE_ELEMENTS_COUNT; k++)
                    vertices.emplace_back(cube_vertices[Faces::BOTTOM_FACE * FACE_ELEMENTS_COUNT + k] + block_coords[k % ELEMENTS_PER_VERTEX]);
            }
        }
    }
}*/



/*constexpr int face_offset = Faces::FRONT_FACE * FACE_ELEMENTS_COUNT;

                    // Use std::copy to copy a block of memory (one face) at once
std::copy(
    cube_vertices + face_offset,
    cube_vertices + face_offset + FACE_ELEMENTS_COUNT,
    std::back_inserter(vertices_container)
);*/




// constexpr float cube_vertices[] = {
//     //   cube coords    texture coords   face //
//     /*front face*/
//     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  // bottom-left  0
//      0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  // bottom-right 1
//      0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  // top-right    2
//      0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  // top-right    2
//     -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,  // top-left     3
//     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  // bottom-left  0

//     /*back face*/
//      0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f,  // top-right    6
//     -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f,  // top-left     7
//     -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f,  // bottom-left  4
//     -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f,  // bottom-left  4
//      0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   1.0f,  // bottom-right 5
//      0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f,  // top-right    6

//     /*left face*/
//     -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   2.0f,  // top-left     7
//     -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   2.0f,  // bottom-left  4
//     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   2.0f,  // bottom-left  0
//     -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   2.0f,  // bottom-left  0
//     -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   2.0f,  // top-left     3
//     -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   2.0f,  // top-left     7

//     /*right face*/
//      0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   3.0f,  // top-right    6
//      0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   3.0f,  // bottom-right 5
//      0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   3.0f,  // bottom-right 1
//      0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   3.0f,  // bottom-right 1
//      0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   3.0f,  // top-right    2
//      0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   3.0f,  // top-right    6

//     /*top face*/
//     -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   4.0f,  // top-left     3
//      0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   4.0f,  // top-right    2
//      0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   4.0f,  // top-right    6
//      0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   4.0f,  // top-right    6
//     -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   4.0f,  // top-left     7
//     -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   4.0f,  // top-left     3

//     /*bottom face*/
//     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   5.0f,  // bottom-left  0
//      0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   5.0f,  // bottom-right 1
//      0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   5.0f,  // bottom-right 5
//      0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   5.0f,  // bottom-right 5
//     -0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   5.0f,  // bottom-left  4
//     -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   5.0f,  // bottom-left  0
// };

// /*
//  * 'Element' is every single float in a vertex buffer. So, 'CUBE_VB_ELEMENTS_COUNT' represents count of floats needed for a hole cube
// */

// constexpr int CUBE_VB_ELEMENTS_COUNT = sizeof(cube_vertices) / sizeof(float);  // Count of elements in cube_vertices vertex buffer (or VB)
// constexpr int FACE_ELEMENTS_COUNT    = CUBE_VB_ELEMENTS_COUNT / 6;
// constexpr int VERTICES_PER_FACE      = 6;
// constexpr int ELEMENTS_PER_VERTEX    = FACE_ELEMENTS_COUNT / VERTICES_PER_FACE;

// void emplace_vertices(std::vector<float>& nontrans_verts, std::vector<float>& trans_verts, int chunk_x, int chunk_z)
// {
//     enum Faces {
//         FRONT_FACE,
//         BACK_FACE,
//         LEFT_FACE,
//         RIGHT_FACE,
//         TOP_FACE,
//         BOTTOM_FACE
//     };

//     const auto& chunk       = *Chunk::chunks[chunk_x][chunk_z];
//     const auto& left_chunk  = *Chunk::chunks[chunk_x - 1][chunk_z];
//     const auto& right_chunk = *Chunk::chunks[chunk_x + 1][chunk_z];
//     const auto& front_chunk = *Chunk::chunks[chunk_x][chunk_z + 1];
//     const auto& back_chunk  = *Chunk::chunks[chunk_x][chunk_z - 1];

//     enum Indexes { X, Y, Z };  // Additional vertex data indices
//     float additional_vertex_data[ELEMENTS_PER_VERTEX] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

//     const auto chunk_blocks  = chunk.Data();
//     const auto lchunk_blocks = left_chunk.Data();
//     const auto rchunk_blocks = right_chunk.Data();
//     const auto fchunk_blocks = front_chunk.Data();
//     const auto bchunk_blocks = back_chunk.Data();

//     for (int block_y = CHUNK_HEIGHT - 1; block_y >= 0; block_y--)
//     {
//         for (int block_z = CHUNK_LENGHT - 1; block_z >= 0; block_z--)
//         {
//             for (int block_x = CHUNK_LENGHT - 1; block_x >= 0; block_x--)
//             {
//                 if (chunk_blocks[block_y][block_z][block_x] == BlockType::NO_BLOCK) {
//                     continue;
//                 }

//                 // std::vector<float>& vertices_container = nontrans_verts;

//                 additional_vertex_data[X] = float(block_x + chunk_x * CHUNK_LENGHT);
//                 additional_vertex_data[Y] = float(block_y);
//                 additional_vertex_data[Z] = float(block_z + chunk_z * CHUNK_LENGHT);
//                 additional_vertex_data[5] = Block::GetBlockShaderValue(chunk_blocks[block_y][block_z][block_x]);

//                 std::vector<float>& vertices_container = ( Block::IsTransparent(chunk_blocks[block_y][block_z][block_x] ) ? 
//                 trans_verts : nontrans_verts );

//                 if (Block::IsTransparent(chunk_blocks[block_y][block_z][block_x]))
//                 {
//                     for (int i = 0; i < CUBE_VB_ELEMENTS_COUNT; i++)
//                     {
//                         vertices_container.emplace_back(cube_vertices[i] + additional_vertex_data[i % ELEMENTS_PER_VERTEX]);
//                     }

//                     continue;
//                 }

//                 // No need to add to texture coordinates and texture slots in the vertices_container array; that's the reason for adding 0-s

//                 if (player.z_pos > additional_vertex_data[Z] + 0.5f &&  // if player is behind the front face, they can't see it
//                    (block_z + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z + 1][block_x]) :  // if there is a block in front, then it's impossible to see front face
//                     Block::IsTransparentOrNoBlock(fchunk_blocks[block_y][0][block_x])))  // if block_z is on the chunk's edge, checks the block in front from the chunk in front
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::FRONT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (player.z_pos < additional_vertex_data[Z] - 0.5f &&  // if player is in front of the back face, they can't see it
//                    (block_z - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z - 1][block_x]) :
//                     Block::IsTransparentOrNoBlock(bchunk_blocks[block_y][CHUNK_LENGHT - 1][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::BACK_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (player.x_pos < additional_vertex_data[X] - 0.5f &&
//                    (block_x - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x - 1]) :
//                     Block::IsTransparentOrNoBlock(lchunk_blocks[block_y][block_z][CHUNK_LENGHT - 1])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::LEFT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (player.x_pos > additional_vertex_data[X] + 0.5f &&
//                    (block_x + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x + 1]) :
//                     Block::IsTransparentOrNoBlock(rchunk_blocks[block_y][block_z][0])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::RIGHT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (player.y_pos > additional_vertex_data[Y] + 0.5f &&
//                    (block_y + 1 >= CHUNK_HEIGHT || Block::IsTransparentOrNoBlock(chunk_blocks[block_y + 1][block_z][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (player.y_pos < additional_vertex_data[Y] - 0.5f &&
//                    (block_y - 1 < 0 || Block::IsTransparentOrNoBlock(chunk_blocks[block_y - 1][block_z][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::BOTTOM_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }
//             }
//         }
//     }
// }

// void emplace_vertices_chunk(std::vector<float>& nontrans_verts, std::vector<float>& trans_verts, int chunk_x, int chunk_z)
// {
//     enum Faces {
//         FRONT_FACE,
//         BACK_FACE,
//         LEFT_FACE,
//         RIGHT_FACE,
//         TOP_FACE,
//         BOTTOM_FACE
//     };

//     const auto& chunk       = *Chunk::chunks[chunk_x][chunk_z];
//     const auto& left_chunk  = *Chunk::chunks[chunk_x - 1][chunk_z];
//     const auto& right_chunk = *Chunk::chunks[chunk_x + 1][chunk_z];
//     const auto& front_chunk = *Chunk::chunks[chunk_x][chunk_z + 1];
//     const auto& back_chunk  = *Chunk::chunks[chunk_x][chunk_z - 1];

//     enum Indexes { X, Y, Z };  // Additional vertex data indices
//     float additional_vertex_data[ELEMENTS_PER_VERTEX] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

//     const auto chunk_blocks  = chunk.Data();
//     const auto lchunk_blocks = left_chunk.Data();
//     const auto rchunk_blocks = right_chunk.Data();
//     const auto fchunk_blocks = front_chunk.Data();
//     const auto bchunk_blocks = back_chunk.Data();

//     for (int block_y = CHUNK_HEIGHT - 1; block_y >= 0; block_y--)
//     {
//         for (int block_z = CHUNK_LENGHT - 1; block_z >= 0; block_z--)
//         {
//             for (int block_x = CHUNK_LENGHT - 1; block_x >= 0; block_x--)
//             {
//                 if (chunk_blocks[block_y][block_z][block_x] == BlockType::NO_BLOCK) {
//                     continue;
//                 }

//                 // std::vector<float>& vertices_container = nontrans_verts;

//                 additional_vertex_data[X] = float(block_x + chunk_x * CHUNK_LENGHT);
//                 additional_vertex_data[Y] = float(block_y);
//                 additional_vertex_data[Z] = float(block_z + chunk_z * CHUNK_LENGHT);
//                 additional_vertex_data[5] = Block::GetBlockShaderValue(chunk_blocks[block_y][block_z][block_x]);

//                 std::vector<float>& vertices_container = ( Block::IsTransparent(chunk_blocks[block_y][block_z][block_x] ) ? 
//                 trans_verts : nontrans_verts );

//                 if (chunk_blocks[block_y][block_z][block_x] == BlockType::WATER)
//                 {
//                     int y = block_y;
//                     for (; chunk_blocks[y][block_z][block_x] == BlockType::WATER; y++);
//                     y--;

//                     float float_y = y - 0.1f; 
//                     additional_vertex_data[Y] = float_y;

//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }

//                     continue;
//                 }

//                 if (Block::IsTransparent(chunk_blocks[block_y][block_z][block_x]))
//                 {
//                     for (int i = 0; i < CUBE_VB_ELEMENTS_COUNT; i++)
//                     {
//                         vertices_container.emplace_back(cube_vertices[i] + additional_vertex_data[i % ELEMENTS_PER_VERTEX]);
//                     }

//                     continue;
//                 }

//                 // No need to add to texture coordinates and texture slots in the vertices_container array; that's the reason for adding 0-s

//                 if (  // if player is behind the front face, they can't see it
//                    (block_z + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z + 1][block_x]) :  // if there is a block in front, then it's impossible to see front face
//                     Block::IsTransparentOrNoBlock(fchunk_blocks[block_y][0][block_x])))  // if block_z is on the chunk's edge, checks the block in front from the chunk in front
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::FRONT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (  // if player is in front of the back face, they can't see it
//                    (block_z - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z - 1][block_x]) :
//                     Block::IsTransparentOrNoBlock(bchunk_blocks[block_y][CHUNK_LENGHT - 1][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::BACK_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (
//                    (block_x - 1 >= 0 ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x - 1]) :
//                     Block::IsTransparentOrNoBlock(lchunk_blocks[block_y][block_z][CHUNK_LENGHT - 1])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::LEFT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (
//                    (block_x + 1 < CHUNK_LENGHT ? Block::IsTransparentOrNoBlock(chunk_blocks[block_y][block_z][block_x + 1]) :
//                     Block::IsTransparentOrNoBlock(rchunk_blocks[block_y][block_z][0])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::RIGHT_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (
//                    (block_y + 1 >= CHUNK_HEIGHT || Block::IsTransparentOrNoBlock(chunk_blocks[block_y + 1][block_z][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::TOP_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }

//                 if (
//                    (block_y - 1 < 0 || Block::IsTransparentOrNoBlock(chunk_blocks[block_y - 1][block_z][block_x])))
//                 {
//                     for (int k = 0; k < FACE_ELEMENTS_COUNT; k++) {
//                         vertices_container.emplace_back(cube_vertices[Faces::BOTTOM_FACE * FACE_ELEMENTS_COUNT + k] + additional_vertex_data[k % ELEMENTS_PER_VERTEX]);
//                     }
//                 }
//             }
//         }
//     }
// }