#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "ShaderProgramService.h"
#include "Util.h"
#include "OpenGLTexture.h"

using namespace std;
using namespace util;

class OpenGLRenderer {
	Shader* shader;
	GLuint vbo, vao, ebo;

	OpenGLTexture* tileset;

	void init(GLuint* shaderProgram);
	void draw(OpenGLTexture* texture, const Drawable drawable);
	void glDraw(OpenGLTexture* texture);

	Mat4 getTransformation(const Rectangle transformation);
	Mat3 getTextureRegion(const Rectangle* region);

public:
	OpenGLRenderer();
	~OpenGLRenderer();
	
	Shader* getShader();

	void setTileset(OpenGLTexture* tileset) { this->tileset = tileset; };

	void draw(OpenGLTexture* texture, const Rectangle rectangle);

	void draw(const Drawable drawable);
};

#endif RENDERER