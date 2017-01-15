#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer() {
	GLuint shaderProgram;

	this->init(&shaderProgram);
	this->shader = new Shader(shaderProgram);
}

OpenGLRenderer::~OpenGLRenderer() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

Shader* OpenGLRenderer::getShader() {
	return this->shader;
}

void OpenGLRenderer::draw(OpenGLTexture* texture, const Rectangle rectangle) {
	Mat4 transform = getTransformation(rectangle);
	Mat3 textureTransform = getTextureRegion(nullptr);

	this->shader->setUniformMatrix3("textureTranslation", textureTransform);
	this->shader->setUniformMatrix4("transform", transform);

	glDraw(texture);
}

void OpenGLRenderer::draw(const Drawable drawable) {
	draw(tileset, drawable);
} 

void OpenGLRenderer::draw(OpenGLTexture* texture, const Drawable drawable) {
	Mat4 transform = getTransformation({ drawable.position, drawable.size });
	Mat3 textureTransform = getTextureRegion(&drawable.textureRegion);

	this->shader->setUniformMatrix3("textureTranslation", textureTransform);
	this->shader->setUniformMatrix4("transform", transform);

	glDraw(texture);
}

Mat4 OpenGLRenderer::getTransformation(const Rectangle transformation) {
	Mat4 transform;

	transform.translate(transformation.position);
	transform.scale(transformation.size);

	return transform;
}

Mat3 OpenGLRenderer::getTextureRegion(const Rectangle* region) {
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

void OpenGLRenderer::glDraw(OpenGLTexture* texture) {
	texture->bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void OpenGLRenderer::init(GLuint* shaderProgram) {
	ShaderProgramService shaderProgramService = ShaderProgramService();
	*shaderProgram = shaderProgramService.createShaderProgram();

	GLfloat vertices[] = {
		// pos			texture
		1.0f, 1.0f,		1.0f, 1.0f, // top right
		1.0f, 0.0f,		1.0f, 0.0f, // bottom right
		0.0f, 0.0f,		0.0f, 0.0f, // bottom left
		0.0f, 1.0f,		0.0f, 1.0f  // top left
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}