PROJ_DIR = "C:/Users/matij/OneDrive/Desktop/Minecraft 10.10.2023"
ARCHITECTURE = -m64
OPTIMIZATION = -O3
STANDARD = c++23

# Use -mwindows to disable cosnole window

all: \
	main \
	gla_base \
	vertexbuffer \
	vblayout \
	indexbuffer \
	uniformbuffer \
	framebuffer \
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
	g++ -std=$(STANDARD) -c -o obj/main.o 				 src/main.cpp
gla_base:
	g++ -std=$(STANDARD) -c -o obj/GlaBase.o 			 src/Gla/GlaBase.cpp
vertexbuffer:
	g++ -std=$(STANDARD) -c -o obj/VertexBuffer.o 		 src/Gla/VertexBuffer.cpp
vblayout:
	g++ -std=$(STANDARD) -c -o obj/VertexBufferLayout.o  src/Gla/VertexBufferLayout.cpp
uniformbuffer:
	g++ -std=$(STANDARD) -c -o obj/UniformBuffer.o 		 src/Gla/UniformBuffer.cpp
indexbuffer:
	g++ -std=$(STANDARD) -c -o obj/IndexBuffer.o 		 src/Gla/IndexBuffer.cpp
vertexarray:
	g++ -std=$(STANDARD) -c -o obj/VertexArray.o 		 src/Gla/VertexArray.cpp
framebuffer:
	g++ -std=$(STANDARD) -c -o obj/FrameBuffer.o 		 src/Gla/FrameBuffer.cpp
shadero:
	g++ -std=$(STANDARD) -c -o obj/Shader.o 			 src/Gla/Shader.cpp
renderer:
	g++ -std=$(STANDARD) -c -o obj/Renderer.o 			 src/Gla/Renderer.cpp
texture:
	g++ -std=$(STANDARD) -c -o obj/Texture.o 			 src/Gla/Texture.cpp
noise:
	g++ -std=$(STANDARD) -c -o obj/Noise.o 				 src/Noise.cpp
chunk:
	g++ -std=$(STANDARD) -c -o obj/Chunk.o 				 src/Chunk.cpp
player:
	g++ -std=$(STANDARD) -c -o obj/Player.o 			 src/Player.cpp
stb:
	g++ -std=$(STANDARD) -c -o obj/stb_image.o 			 src/stb/stb_image.cpp

compile:
	g++ -Wall -std=$(STANDARD) $(ARCHITECTURE) $(OPTIMIZATION) -o Minecraft \
	obj/VertexBufferLayout.o obj/IndexBuffer.o obj/VertexBuffer.o obj/UniformBuffer.o obj/FrameBuffer.o obj/VertexArray.o obj/GlaBase.o \
	obj/Shader.o obj/Renderer.o obj/Texture.o obj/Noise.o obj/Chunk.o obj/Player.o obj/main.o obj/stb_image.o \
	-l:libglfw3.a -lopengl32 -lGdi32 -lglu32 -lglew32

run:
	./Minecraft