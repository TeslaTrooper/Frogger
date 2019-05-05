#ifndef RENDERER
#define RENDERER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <ShaderFactory.h>
#include <BaseOpenGLRenderer.h>
#include <Texture.h>

#include "Shader.h"
#include "Util.h"
#include "Game.h"

#define TRANS_R 174
#define TRANS_G 54
#define TRANS_B 158

using namespace std;
using namespace util;

class OpenGLRenderer : public BaseOpenGLRenderer {

	static const float vertices[];
	static const int indices[];
	static const int sizes[];

	Shader* shader;

	Texture* tileset;
	Texture* background;

	Game* game;
	RenderData data;

	Bindable init();

	Mat3 getTextureRegion(const util::Rectangle* region) const;

	void prepareShaders(const Mat4& transformation) const;
	void prepareShaders(const Mat4& transformation, const util::Rectangle* textureRegion) const;

	void initProjection() const;

	void render() const override;

	void setup() override;

public:
	OpenGLRenderer(Game* game) : game(game) {};
	~OpenGLRenderer();
};

#endif RENDERER