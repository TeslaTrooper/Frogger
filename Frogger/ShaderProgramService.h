#ifndef SHADER_PROGRAM_SERVICE
#define SHADER_PROGRAM_SERVICE

#include <GL/glew.h>
#include <iostream>

class ShaderProgramService {
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 position;\n"
		"layout (location = 1) in vec2 texture;\n"
		"out vec2 textureCoords;\n"
		"uniform mat4 transform;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
			"gl_Position = projection * transform * vec4(position, 0.0f, 1.0f);\n"
			"textureCoords = texture;\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec2 textureCoords;\n"
		"out vec4 color;\n"
		"uniform vec3 myColor;\n"
		"uniform sampler2D tex;\n"
		"void main() {\n"
			"color = texture(tex, textureCoords);\n"
		"}\n\0";

	void compileShader(GLuint shader, const GLchar* shaderSource);

	GLuint createShader(GLenum shaderType, const GLchar* shaderSource);

public:
	ShaderProgramService();
	~ShaderProgramService();

	GLuint createShaderProgram();

};

#endif SHADER_PROGRAM_SERVICE