#pragma once

#include "SDL_opengl.h"
#include "SDL.h"

class Graphics {
public:
	static void init();
	static void update();
	static void shutdown();

private:
	static GLuint compileShader(GLenum shaderType, const char * shaderCode);
	static void checkError(const char * msg);

	static SDL_GLContext context;
	static GLint p1Location;
};

