#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Util.h"
#include "OpenGLTexture.h"
#include "BaseOpenGLRenderer.h"
#include "Game.h"
#include "ShaderProgram.h"

using namespace std;
using namespace util;

class OpenGLRenderer : public BaseOpenGLRenderer {

	static const float vertices[];
	static const int indices[];
	static const int sizes[];

	Shader* shader;

	Texture* tileset;
	Texture* background;

	Game* logic;
	RenderData data;

	Bindable init();

	Mat3 getTextureRegion(const util::Rectangle* region) const;

	void prepareShaders(const Mat4& transformation) const;
	void prepareShaders(const Mat4& transformation, const Rectangle* textureRegion) const;

	void initProjection() const;

	void render() const override;

public:
	OpenGLRenderer(Game* logic);
	~OpenGLRenderer();


	/*
		Setzt das tileset, das der Renderer verwenden soll.
		@param tileset ist das zu verwendende Tileset.
	*/
	void setTileset(OpenGLTexture* tileset) { this->tileset = tileset; };
};

#endif RENDERER