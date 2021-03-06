#include "Vector.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Vector::create(const glm::vec3& directionPosition, const glm::vec3& directionVector, const glm::vec3& color)
{
	_color = color;
	loadData();
	loadShaders(false, std::map<const GLenum, const std::string>{
		{
			GL_VERTEX_SHADER, "Shaders/sampler2DVS.glsl"
		},
		{ GL_FRAGMENT_SHADER, "Shaders/sampler2DFS.glsl" }});
	loadBuffers();
	model = glm::translate(model, directionPosition);
	model = glm::rotate(model, glm::radians(90.0f), directionVector);
}

void Vector::update(glm::mat4& view, glm::mat4& projection)
{
	this->view = view;
	this->projection = projection;
}

void Vector::render()
{
	// Bind our shaders for use
	shaders.use();

	// Send our uniform attributes to the GPU
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind the VAO, draw the object, then unbind the vao + shaders
	glBindVertexArray(vao);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	shaders.unuse();
}

void Vector::setPos(const glm::vec3& position)
{
	model = glm::mat4();
	model = glm::translate(model, position);
}

void Vector::loadData()
{
	std::initializer_list<glm::vec3> tempPos{
		glm::vec3(-0.01f,  0.01f,  0.6f),
		glm::vec3( 0.01f,  0.01f,  0.6f),
		glm::vec3(-0.01f, -0.01f,  0.6f),
		glm::vec3( 0.01f, -0.01f,  0.6f),
				   	 	   
		glm::vec3(-0.01f,  0.01f,  -0.6f),
		glm::vec3( 0.01f,  0.01f,  -0.6f),
		glm::vec3(-0.01f, -0.01f,  -0.6f),
		glm::vec3( 0.01f, -0.01f,  -0.6f),

		glm::vec3(-0.1f,  0.01f,  0.6f),
		glm::vec3( 0.1f,  0.01f,  0.6f),
		
		glm::vec3(-0.1f, -0.01f,  0.6f),
		glm::vec3( 0.1f, -0.01f,  0.6f),

		glm::vec3(0.0f, 0.0f, 1.0f)
	};
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
		5,7,

		1, 8,
		0, 9,
		2, 10,
		3, 11,

		8,10,
		9,11,

		8, 12,
		9, 12,
		10, 12,
		11, 12
	};
	Vertex tempVert;
	tempVert.Color = _color;
	for(const auto& it: tempPos)
	{
		tempVert.Position = it;
		vertices.push_back(tempVert);
	}
}
