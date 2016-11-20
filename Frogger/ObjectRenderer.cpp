#include "Renderer.h"

Renderer::Renderer() {
	GLuint shaderProgram;

	this->textures = new std::vector<Texture>();
	this->init(&shaderProgram);
	this->shader = new Shader(shaderProgram);
}

Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

Shader* Renderer::getShader() {
	return this->shader;
}

void Renderer::draw(Texture* texture, Vec2 position, Vec2 size) {
	Mat4 transform;
	
	transform.translate(position);
	transform.scale(size);

	this->shader->setUniformMatrix4("transform", transform);

	texture->bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::draw(Drawable drawable) {
	draw(drawable.texture, drawable.position, drawable.size);
}

void Renderer::init(GLuint* shaderProgram) {
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