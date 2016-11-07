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

void Renderer::draw(Texture* texture, glm::vec2 position, glm::vec2 size, glm::vec3 color) {
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(position, 0.0f));

	transform = glm::translate(transform, glm::vec3(0.5f*size.x, 0.5f*size.y, 0.0f));
	//transform = glm::rotate(transform, (GLfloat)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.0, 0.0, 1.0));
	transform = glm::translate(transform, glm::vec3(-0.5f*size.x, -0.5f*size.y, 0.0f));

	transform = glm::scale(transform, glm::vec3(size, 1.0f));

	this->shader->setVector3("myColor", color);
	this->shader->setUniformMatrix4("transform", transform);
	//this->shader->setVector2("texCoords", glm::vec2(1.0f, 1.0f));

	texture->bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
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