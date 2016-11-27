#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "ShaderProgramService.h"
#include "Util.h"
#include "Texture.h"

using namespace std;

class Renderer {
	Shader* shader;
	GLuint vbo, vao, ebo;

	Texture* tileset;

	void init(GLuint* shaderProgram);
	void draw(Texture* texture, const Drawable drawable);
	void glDraw(Texture* texture);

	Mat4 getTransformation(const Rectangle transformation);
	Mat3 getTextureRegion(const Rectangle* region);

public:
	Renderer();
	~Renderer();
	
	Shader* getShader();

	void setTileset(Texture* tileset) { this->tileset = tileset; };

	void draw(Texture* texture, const Rectangle rectangle);

	void draw(const Drawable drawable);
};

#endif RENDERER