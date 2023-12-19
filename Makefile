PROJ_DIR = "C:/Users/matij/OneDrive/Desktop/Minecraft 10.10.2023"
ARCHITECTURE = -m64
OPTIMIZATION = -O0
STANDARD = c++23

# Use -mwindows to disable cosnole window

all: \
	main \
	gla_base \
	vertexbuffer \
	vblayout \
	indexbuffer \
	uniformbuffer \
	vertexarray \
	shadero \
	renderer \
	texture \
	noise \
	chunk \
	player \
	stb \
	compile

main:
	g++ -c -o obj/main.o 				src/main.cpp
gla_base:
	g++ -c -o obj/GlaBase.o 			src/Gla/GlaBase.cpp
vertexbuffer:
	g++ -c -o obj/VertexBuffer.o 		src/Gla/VertexBuffer.cpp
vblayout:
	g++ -c -o obj/VertexBufferLayout.o  src/Gla/VertexBufferLayout.cpp
uniformbuffer:
	g++ -c -o obj/UniformBuffer.o 		src/Gla/UniformBuffer.cpp
indexbuffer:
	g++ -c -o obj/IndexBuffer.o 		src/Gla/IndexBuffer.cpp
vertexarray:
	g++ -c -o obj/VertexArray.o 		src/Gla/VertexArray.cpp
shadero:
	g++ -c -o obj/Shader.o 				src/Gla/Shader.cpp
renderer:
	g++ -c -o obj/Renderer.o 			src/Gla/Renderer.cpp
texture:
	g++ -c -o obj/Texture.o 			src/Gla/Texture.cpp
noise:
	g++ -c -o obj/Noise.o 				src/Noise.cpp
chunk:
	g++ -c -o obj/Chunk.o 				src/Chunk.cpp
player:
	g++ -c -o obj/Player.o 				src/Player.cpp
stb:
	g++ -c -o obj/stb_image.o 			src/stb/stb_image.cpp

compile:
	g++ -Wall -std=$(STANDARD) $(ARCHITECTURE) $(OPTIMIZATION) -o Minecraft \
	obj/VertexBufferLayout.o obj/IndexBuffer.o obj/VertexBuffer.o obj/UniformBuffer.o obj/VertexArray.o obj/GlaBase.o \
	obj/Shader.o obj/Renderer.o obj/Texture.o obj/Noise.o obj/Chunk.o obj/Player.o obj/main.o obj/stb_image.o \
	-l:libglfw3.a -lopengl32 -lGdi32 -lglu32 -lglew32

run:
	./Minecraft




# 32 bit version

32bit: \
	main_32bit \
	definitions_32bit \
	vertexbuffer_32bit \
	vblayout_32bit \
	indexbuffer_32bit \
	uniformbuffer_32bit \
	vertexarray_32bit \
	shadero_32bit \
	renderer_32bit \
	texture_32bit \
	noise_32bit \
	chunk_32bit \
	stb_32bit \
	compile_32bit

main_32bit:
	g++ -c -o obj32/main.o 					src/main.cpp
definitions_32bit:
	g++ -c -o obj32/Definitions.o 			src/Definitions.cpp
vertexbuffer_32bit:
	g++ -c -o obj32/VertexBuffer.o 			src/VertexBuffer.cpp
vblayout_32bit:
	g++ -c -o obj32/VertexBufferLayout.o  	src/VertexBufferLayout.cpp
uniformbuffer_32bit:
	g++ -c -o obj32/UniformBuffer.o 		src/UniformBuffer.cpp
indexbuffer_32bit:
	g++ -c -o obj32/IndexBuffer.o 			src/IndexBuffer.cpp
vertexarray_32bit:
	g++ -c -o obj32/VertexArray.o 			src/VertexArray.cpp
shadero_32bit:
	g++ -c -o obj32/Shader.o 				src/Shader.cpp
renderer_32bit:
	g++ -c -o obj32/Renderer.o	 			src/Renderer.cpp
texture_32bit:
	g++ -c -o obj32/Texture.o 				src/Texture.cpp
noise_32bit:
	g++ -c -o obj32/Noise.o 				src/Noise.cpp
chunk_32bit:
	g++ -c -o obj32/Chunk.o 				src/Chunk.cpp
stb_32bit:
	g++ -c -o obj32/stb_image.o 			src/stb/stb_image.cpp

compile_32bit:
	g++ -Wall -std=$(STANDARD) -m32 $(OPTIMIZATION) -o bin32/Minecraft \
	obj32/VertexBufferLayout.o obj32/IndexBuffer.o obj32/VertexBuffer.o obj32/UniformBuffer.o obj32/VertexArray.o \
	obj32/Definitions.o obj32/Shader.o obj32/Renderer.o obj32/Texture.o obj32/Noise.o obj32/Chunk.o obj32/main.o obj32/stb_image.o \
	-llibglfw3 -lopengl32 -lGdi32 -lglu32 -lglew32

run_32bit:
	./bin32/Minecraft