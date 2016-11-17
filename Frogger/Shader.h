#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Vec2.h"
#include "Mat4.h"

class Shader {

	GLuint shaderProgram;

public:
	Shader(GLuint shaderProgram);
	~Shader();

	void setUniformMatrix4(const GLchar* uniform, Mat4 value);
	void setVector3(const GLchar* uniform, glm::vec3 value);
	void setInteger(const GLchar* uniform, GLint value);
	void setVector2(const GLchar* uniform, Vec2 value);

	void use();
};

#endif SHADER