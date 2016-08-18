#include "Drawable.h"
#include <glm/gtc/type_ptr.hpp>

de::Drawable::Drawable() : vao(0), vbo(0), ebo(0), modelLoc(0), viewLoc(0), projLoc(0)
{
}

de::Drawable::~Drawable()
{
	indices.clear();
	vertices.clear();
	vao = 0, vbo = 0, ebo = 0, modelLoc = 0, viewLoc = 0, projLoc = 0;
}

void de::Drawable::loadData()
{
	std::initializer_list<Vertex> tempVerts
	{
		Vertex(glm::vec3(-0.5f,  0.5f,  1.0f), glm::vec3(0.1f), glm::vec2(0)),
		Vertex(glm::vec3(0.5f,  0.5f,  1.0f), glm::vec3(0.1f), glm::vec2(0)),
		Vertex(glm::vec3(-0.5f, -0.5f,  1.0f), glm::vec3(0.2f), glm::vec2(0)),
	};
	for (auto vertIt : tempVerts)
	{
		vertices.push_back(vertIt);
	}
	loadShaders();
	loadBuffers();
}

void de::Drawable::loadShaders()
{
	shaders.addShader(GL_VERTEX_SHADER, "Res/Shaders/drawable.vs");
	shaders.addShader(GL_FRAGMENT_SHADER, "Res/Shaders/drawable.fs");
	shaders.linkShaders();
}

void de::Drawable::loadBuffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	if(!indices.empty())
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Position)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Color)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void de::Drawable::update()
{

}

void de::Drawable::render()
{
	shaders.use();
	glBindVertexArray(vao);
	if (!indices.empty())
	{
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glBindVertexArray(0);
	shaders.unuse();
}