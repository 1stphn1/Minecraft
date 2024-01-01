#pragma once

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>
// #include <exception>

/*#define DEBUG_MODE

#define GLAssert(expression)    if (!expression) { std::exit(EXIT_FAILURE); }

#ifdef DEBUG_MODE
    #define LOG(output)  std::cout << output << '\n';

    #define GLCall(expression)  GLClearError();\
                                expression;\
                                GLAssert(GLLogCall(#expression, __FILE__, __LINE__))
#else
    #define LOG(output)         { }
    #define GLCall(expression)  expression
#endif  // DEBUG_MODE

std::string GLErrorToString(GLenum error);
void        GLClearError();
bool        GLLogCall(const char *function_name, const char *file_name, int line);*/

constexpr int WINDOW_WIDTH  = 1280;
constexpr int WINDOW_HEIGHT = 960;

constexpr int CHUNK_LENGHT = 16;
// constexpr int CHUNK_HEIGHT = 256;
constexpr int CHUNK_HEIGHT = 128;

constexpr int CHUNKS_ACROSS_X_AXIS = 1000;
constexpr int CHUNKS_ACROSS_Z_AXIS = 1000;

constexpr int VIEW_DISTANCE  = 5;  // View distance in chunks
constexpr int VISIBLE_CHUNKS = VIEW_DISTANCE * 2 * VIEW_DISTANCE * 2;

constexpr float FOV_Y = 10.0f;
const     float FOV_X = glm::degrees( 2 * glm::atan(glm::tan( glm::radians(FOV_Y) * 0.5f ) * ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)) );

const glm::vec3 x_axis(1.0f, 0.0f, 0.0f);  // Rotate around the x-axis
const glm::vec3 y_axis(0.0f, 1.0f, 0.0f);  // Rotate around the y-axis
const glm::vec3 z_axis(0.0f, 0.0f, 1.0f);
const glm::mat4 PROJECTION_MTR = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, -8.0f, 8.0f) * glm::perspective<float>(glm::radians(FOV_Y), 1280.0f / 960.0f, 0.1f, 1.0f);

constexpr float BLOCK_SIDE_LENGHT = 1.0f;
constexpr int   WATER_LEVEL = 30;