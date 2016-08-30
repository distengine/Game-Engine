#include "Drawable.h"

Drawable::Drawable(): modelLoc(0), viewLoc(0), projLoc(0), textureLocation(0), vao(), vbo(0), ebo(0)
{
}

// cleans up our shaders, textures, and buffers
Drawable::~Drawable()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	shaders.deleteShaders();
	texture.deleteTexture();
}

// load the buffers
void Drawable::loadBuffers()
{
	glCreateVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	if (!indices.empty())
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Position)));
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Color)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, UV)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// Load the shaders
void Drawable::loadShaders(const bool& textured, std::map<const GLenum, const std::string> shaderTypes)
{
	// Adds our shaders to our maps and links them
	for (auto& it : shaderTypes)
	{
		shaders.addShader(it.first, it.second);
	}
	shaders.linkShaders();

	// Get uniform locations
	modelLoc = shaders.getUniformLocation("model");
	viewLoc = shaders.getUniformLocation("view");
	projLoc = shaders.getUniformLocation("projection");
	if (textured)
	{
		textureLocation = shaders.getUniformLocation("t_Texture");
	}
}