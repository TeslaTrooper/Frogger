#include "ShaderProgramService.h"

ShaderProgramService::ShaderProgramService() {}

GLuint ShaderProgramService::createShaderProgram() {
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		std::cout << "Error loading shader program!";
	}

	return shaderProgram;
}

void ShaderProgramService::compileShader(GLuint shader, const GLchar* shaderSource) {
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		std::cout << "Error compiling shader!";
	}
}

GLuint ShaderProgramService::createShader(GLenum shaderType, const GLchar* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	compileShader(shader, shaderSource);

	return shader;
}

ShaderProgramService::~ShaderProgramService() {}