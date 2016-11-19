#include "Shader.h"

Shader::Shader(GLuint shaderProgram) {
	this->shaderProgram = shaderProgram;
}

Shader::~Shader() {}

void Shader::setUniformMatrix4(const GLchar* uniform, Mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, uniform), 1, GL_FALSE, Mat4::ptr(value));
}

void Shader::setInteger(const GLchar* uniform, GLint value) {
	glUniform1i(glGetUniformLocation(this->shaderProgram, uniform), value);
}

void Shader::setVector2(const GLchar* uniform, Vec2 value) {
	glUniform2f(glGetUniformLocation(this->shaderProgram, uniform), value.x, value.y);
}

void Shader::use() {
	glUseProgram(this->shaderProgram);
}