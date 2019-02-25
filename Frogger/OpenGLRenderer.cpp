#include "OpenGLRenderer.h"

const int OpenGLRenderer::indices[] = {
	0, 1, 3,
	1, 2, 3
};

const float OpenGLRenderer::vertices[] = {
	// pos			texture
	1.0f, 1.0f,		1.0f, 1.0f, // top right
	1.0f, 0.0f,		1.0f, 0.0f, // bottom right
	0.0f, 0.0f,		0.0f, 0.0f, // bottom left
	0.0f, 1.0f,		0.0f, 1.0f  // top left
};

const int OpenGLRenderer::sizes[] = {
	2, 2
};

OpenGLRenderer::OpenGLRenderer(Game* logic) : logic(logic) {
	tileset = new OpenGLTexture("../textures/tileset.bmp");
	background = new OpenGLTexture("../textures/bg.bmp");

	ShaderProgram standardShaderProgramm;
	GLuint shaderProgram = standardShaderProgramm.createShaderProgram("shader.vert", "shader.frag");
	this->shader = new Shader(shaderProgram);

	initProjection();
	data = configure(init(), GL_TRIANGLES);
}

OpenGLRenderer::~OpenGLRenderer() {
	glDeleteVertexArrays(1, &data.vao);
	glDeleteBuffers(1, &data.vbo);
	glDeleteBuffers(1, &data.ebo);
}

void OpenGLRenderer::initProjection() const {
	shader->use();
	shader->setUniformMatrix4("projection", Projection::getOrthographicProjection(WINDOW_WIDTH, WINDOW_HEIGHT));
}

void OpenGLRenderer::render() const {
	Drawable bgDrawable = { Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f), {Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f)} };
	prepareShaders(bgDrawable, false);
	background->bind();
	BaseOpenGLRenderer::draw(data);

	tileset->bind();
	map<DrawableType, std::vector<Drawable>> drawables = logic->getDrawables();
	for (int i = 0; i < drawables.at(DrawableType::OBJECT).size(); i++) {
		Drawable d = drawables.at(DrawableType::OBJECT).at(i);
		prepareShaders(d, true);
		BaseOpenGLRenderer::draw(data);
	}
	for (int i = 0; i < drawables.at(DrawableType::FONT).size(); i++) {
		Drawable d = drawables.at(DrawableType::FONT).at(i);
		prepareShaders(d, true);
		BaseOpenGLRenderer::draw(data);
	}
}

void OpenGLRenderer::prepareShaders(const Drawable& drawable, bool useRegion) const {
	Mat4 transform = Mat4::getTransformation(drawable.position, drawable.size);

	Mat3 textureTransform;
	if (useRegion)
		textureTransform = getTextureRegion(&drawable.textureRegion);

	this->shader->setUniformMatrix3("textureTranslation", textureTransform);
	this->shader->setUniformMatrix4("transform", transform);
}

Mat3 OpenGLRenderer::getTextureRegion(const Rectangle* region) const {
	Mat3 textureTransform;

	if (region == nullptr) {
		return textureTransform;
	}

	Vec2 textureTranslator = Vec2(region->position.x * X_TILE_SIZE / tileset->getWidth(), region->position.y * Y_TILE_SIZE / tileset->getHeight());
	textureTransform.translate(textureTranslator);

	Vec2 textureScaler = Vec2(region->size.x * X_TILE_SIZE / tileset->getWidth(), region->size.y * Y_TILE_SIZE / tileset->getHeight());
	textureTransform.scale(textureScaler);

	return textureTransform;
}

Bindable OpenGLRenderer::init() {
	VertexData vd = { vertices, 4, 4 };
	IndexData id = { indices, 6 };
	AttributeData ad = { sizes, 2 };

	return { vd, id, ad };
}