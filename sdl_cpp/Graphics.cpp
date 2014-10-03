#include <cassert>
#include <sstream>
#include "SDL_opengl.h"
#include "SDL.h"
#include "Main.h"
#include "Util.h"
#include "Graphics.h"

SDL_GLContext Graphics::context;

GLint Graphics::p1Location;

void Graphics::init() {
	// Get function pointers as needed.

	typedef void (APIENTRY * glGenVertexArrays_Func)(GLsizei n, GLuint * arrays);
	typedef void (APIENTRY * glBindVertexArray_Func)(GLuint array);

	glGenVertexArrays_Func glGenVertexArrays = 0;
	glBindVertexArray_Func glBindVertexArray = 0;

	glGenVertexArrays = (glGenVertexArrays_Func) SDL_GL_GetProcAddress("glGenVertexArrays");
	glBindVertexArray = (glBindVertexArray_Func) SDL_GL_GetProcAddress("glBindVertexArray");

	// Create context and setup viewport.

	context = SDL_GL_CreateContext(Main::window);
	glViewport(0, 0, Main::width, Main::height);

	// Create vertex buffer object to draw quad.

	GLfloat quadVertices[] = {
		-1.0,  1.0, 
		 1.0,  1.0,
		-1.0, -1.0,
		 1.0,  1.0,
		 1.0, -1.0,
		-1.0, -1.0 
	};
	GLuint quadVBO;
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, quadVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Compile shaders.

	const char * vertexCode = 
		"#version 150                                                \n"
		"in vec2 pos;                                                \n"
		"uniform vec2 p1;                                            \n"
		"void main() {                                               \n"
		"   gl_Position = vec4(pos, 0.0 * p1.x, 1.0);                       \n"
		"}                                                           \n";

	const char * fragmentCode =
		"#version 150                                                           \n"
		"out vec4 outColor;                                                     \n"
		"uniform vec2 p1;                                            \n"
		"float rand(vec2 co) {                                                  \n"
		"    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);  \n"
		"}                                                                      \n"
		"void main() {                                                          \n"
		"    float d = distance(vec2(gl_FragCoord), p1) / 200;                    \n"
		//"    float d = length(vec2(gl_FragCoord)) / 200;                    \n"
		"    outColor = vec4(d, 0.0, 0.0, 1.0);                                 \n"
		"}                                                                      \n";

	GLuint vertexShader   = compileShader(GL_VERTEX_SHADER   , vertexCode   );
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER , fragmentCode );

	GLuint program = glCreateProgram();
	checkError("glCreateProgram");
	if (program == 0) {
		Util::fatal("glCreateProgram returned 0.");
	}

	glAttachShader(program, vertexShader);
	checkError("attached vertex shader");
	glAttachShader(program, fragmentShader);
	checkError("attached fragment shader");

	glLinkProgram(program);
	checkError("glLinkProgram");

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	checkError("glGetProgramiv");
	if (!linked) {
		GLint infoLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		checkError("glGetProgramiv");
		assert(infoLen > 1);
		char * infoLog = (char *) malloc(sizeof(char) * infoLen );
		glGetProgramInfoLog(program, infoLen, NULL, infoLog);
		checkError("glGetProgramInfoLog");
		std::stringstream ss;
		ss << "Shader link error: \n" << infoLog; 
		Util::fatal(ss.str().c_str());
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	checkError("glBindVertexArray");

	glUseProgram(program);

	GLint posAttrib = glGetAttribLocation(program, "pos");
	checkError("glGetAttribLocation");
	assert(posAttrib != -1);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(posAttrib);
	checkError("glEnableVertexAttribArray");

	p1Location = glGetUniformLocation(program, "p1");
	checkError("glGetUniformLocation");
	assert(p1Location != -1);
}

void Graphics::update() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUniform2f(p1Location, Main::width / 2, Main::height / 2);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkError("glDrawArrays");

	SDL_GL_SwapWindow(Main::window);
}

void Graphics::shutdown() {
	SDL_GL_DeleteContext(context);
}

void Graphics::checkError(const char * msg) {
	GLenum errorCode = glGetError();
	if (errorCode == GL_NO_ERROR) return;
	std::stringstream ss;
	ss << "OpenGL Error: " << errorCode << "\n" << msg;
	Util::fatal(ss.str().c_str());
}

GLuint Graphics::compileShader(GLenum shaderType, const char * shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	checkError("glCreateShader");
	if (shader == 0) {
		Util::fatal("glCreateShader() returned 0.");
		return 0;
	}

	glShaderSource(shader, 1, &shaderCode, NULL);
	checkError("glShaderSource");
   
	glCompileShader(shader);
	checkError("glCompileShader");

	// Check the compile status.
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	checkError("glGetShaderiv");

	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);      
		checkError("glGetShaderiv");
		assert(infoLen > 1);
		char * infoLog = (char *) malloc(sizeof(char) * infoLen);
		glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
		std::stringstream ss;
		ss << "Shader compilation error:\n" << infoLog;
		Util::fatal(ss.str().c_str());
	}

	return shader;
}

