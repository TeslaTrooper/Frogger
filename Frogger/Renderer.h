#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"
#include "ShaderProgramService.h"
#include "Texture.h"
#include "Vec2.h"

class Renderer {
	Shader* shader;
	GLuint vbo, vao, ebo;
	std::vector<Texture>* textures;

	void init(GLuint* shaderProgram);

public:
	Renderer();
	~Renderer();
	
	Shader* getShader();
	void draw(Texture* texture, Vec2 position, Vec2 size, glm::vec3 color);

	void draw(Vec2 position, Vec2 size);
};

#endif RENDERER