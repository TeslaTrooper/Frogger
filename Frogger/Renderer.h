#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "ShaderProgramService.h"
#include "Util.h"
#include "Texture.h"

class Renderer {
	Shader* shader;
	GLuint vbo, vao, ebo;
	std::vector<Texture>* textures;

	Texture* tileset;

	void init(GLuint* shaderProgram);

	void draw(Texture* texture, Drawable drawable);

public:
	Renderer();
	~Renderer();
	
	Shader* getShader();

	void setTileset(Texture* tileset) { this->tileset = tileset; };

	void draw(Texture* texture, Vec2 position, Vec2 size);

	void draw(Drawable drawable);
};

#endif RENDERER