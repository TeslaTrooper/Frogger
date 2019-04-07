#include "OpenGLRenderer.h"

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
	Mat4 backgroundTransformation = Mat4::getTransformation(Vec2(0.0f, 0.0f), Vec2(560.0f, 540.0f));
	prepareShaders(backgroundTransformation);
	background->bind();
	BaseOpenGLRenderer::draw(data);

	tileset->bind();
	map<DrawableType, vector<Drawable>> drawables = logic->getDrawables();
	for (int i = 0; i < drawables.at(DrawableType::OBJECT).size(); i++) {
		Drawable d = drawables.at(DrawableType::OBJECT).at(i);
		prepareShaders(d.transformation, &d.textureRegion);
		BaseOpenGLRenderer::draw(data);
	}
	for (int i = 0; i < drawables.at(DrawableType::FONT).size(); i++) {
		Drawable d = drawables.at(DrawableType::FONT).at(i);
		prepareShaders(d.transformation, &d.textureRegion);
		BaseOpenGLRenderer::draw(data);
	}
}

void OpenGLRenderer::prepareShaders(const Mat4& transformation) const {
	Mat3 identity;

	this->shader->setUniformMatrix3("textureTranslation", identity);
	this->shader->setUniformMatrix4("transform", transformation);
}

void OpenGLRenderer::prepareShaders(const Mat4& transformation, const Rectangle* textureRegion) const {
	this->shader->setUniformMatrix3("textureTranslation", getTextureRegion(textureRegion));
	this->shader->setUniformMatrix4("transform", transformation);
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
	VertexData vd = { ModelData::vertices, 4, 4 };
	IndexData id = { ModelData::indices, 6 };
	AttributeData ad = { ModelData::sizes, 2 };

	return { vd, id, ad };
}