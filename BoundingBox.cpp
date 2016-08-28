#include "BoundingBox.h"
#include "algorithm"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

void BoundingBox::create(const std::vector<Vertex>& verts)
{
	for (const auto& it : verts)
	{
		const auto& itPos = it.Position;
		_minX = std::min(itPos.x, _minX);
		_maxX = std::max(itPos.x, _maxX);
		_minY = std::min(itPos.y, _minY);
		_maxY = std::max(itPos.y, _maxY);
		_minZ = std::min(itPos.z, _minZ);
		_maxZ = std::max(itPos.z, _maxZ);
	}

	std::vector<glm::vec3> tempPos
	{
		glm::vec3(_minX, _maxY, _minZ),
		glm::vec3(_maxX, _maxY, _minZ),
		glm::vec3(_minX, _maxY, _maxZ),
		glm::vec3(_maxX, _maxY, _maxZ),

		glm::vec3(_minX, _minY, _minZ),
		glm::vec3(_maxX, _minY, _minZ),
		glm::vec3(_minX, _minY, _maxZ),
		glm::vec3(_maxX, _minY, _maxZ),
	};

	Vertex tempVert;
	tempVert.Color = glm::vec3(1.0f, 0.0f, 0.0f);
	for(const auto& it : tempPos)
	{
		tempVert.Position = it;
		vertices.push_back(tempVert);
	}

	indices = std::vector<GLuint>{
		// Front
		0,4,
		4,5,
		5,1,
		1,0,

		// Back
		2,6,
		6,7,
		7,3,
		3,2,
		// Sides
		0,2,
		1,3,
		4,6,
		5,7
	};
	loadBuffers();
	loadShaders(false, std::map<const GLenum, const std::string>{
		{
			GL_VERTEX_SHADER, "Shaders/sampler2DVS.glsl"
		},
		{ GL_FRAGMENT_SHADER, "Shaders/sampler2DFS.glsl" }});
}

void BoundingBox::update(const glm::mat4& m, glm::mat4& view, glm::mat4& projection)
{
	model = m;
	_xPos = model[3][0];
	_yPos = model[3][1];
	_zPos = model[3][2];
	_min = glm::vec3(((_minX + 1) / 2) + _xPos, ((_minY + 1) / 2) + _yPos, ((_minZ + 1) / 2) + _zPos);
	_max = glm::vec3(((_maxX + 1) / 2) + _xPos, ((_maxY + 1) / 2) + _yPos, ((_maxZ + 1) / 2) + _zPos);
	this->view = view;
	this->projection = projection;
}

bool BoundingBox::testCollision(const BoundingBox& otherBox)
{
	
	   if((_min.x <= otherBox._max.x && _max.x >= otherBox._min.x) &&
          (_min.y <= otherBox._max.y && _max.y >= otherBox._min.y) &&
          (_min.z <= otherBox._max.z && _max.z >= otherBox._min.z))
	{
		return true;
	}
	return false;
}

void BoundingBox::render()
{
	shaders.use();
	glBindVertexArray(vao);
	// Send our uniform attributes to the GPU
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glPointSize(20.0f);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	shaders.unuse();
}

void BoundingBox::loadBuffers()
{
	glCreateVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, Color)));
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}