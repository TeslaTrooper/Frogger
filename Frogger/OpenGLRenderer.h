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

	Mat4 getTransformation(const util::Rectangle transformation);
	Mat3 getTextureRegion(const util::Rectangle* region);

public:
	OpenGLRenderer();
	~OpenGLRenderer();
	

	/*
		@return gibt die den Shader des Renderes zurück.
	*/
	Shader* getShader();


	/*
		Setzt das tileset, das der Renderer verwenden soll.
		@param tileset ist das zu verwendende Tileset.
	*/
	void setTileset(OpenGLTexture* tileset) { this->tileset = tileset; };


	/*
		Zeichnet eine Textur mit gegebener Position und Größe.
		@param rectangle beinhaltet die Position, sowie Größe.
	*/
	void draw(OpenGLTexture* texture, const util::Rectangle rectangle);


	/*
		Zeichnet ein Drawable.
		@param drawable das gezeichnet werden soll.
	*/
	void draw(const Drawable drawable);
};

#endif RENDERER