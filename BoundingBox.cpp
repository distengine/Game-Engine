#include "BoundingBox.h"
#include "algorithm"
#include <iostream>

void BoundingBox::create(const Cube& cube)
{
	for(const auto& it :cube.vertices)
	{
		const auto& itPos = it.Position;
		_minX = std::min(itPos.x, _minX);
		_maxX = std::max(itPos.x, _maxX);
		_minY = std::min(itPos.y, _minY);
		_maxY = std::max(itPos.y, _maxY);
		_minZ = std::min(itPos.z, _minZ);
		_maxZ = std::max(itPos.z, _maxZ);
	}
	loadBuffers();
}

void BoundingBox::update(glm::mat4& view, glm::mat4& projection)
{

}

void BoundingBox::render()
{

}

void BoundingBox::loadBuffers()
{
	glCreateVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Position)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BoundingBox::loadShaders(const bool& textured, std::map<const GLenum, const std::string> shaderTypes)
{

}