#include "Cube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Create a cube with a color
void Cube::create(const glm::vec3& cubePosition, const glm::vec3& size, const glm::vec3& cubeColor)
{
	_position = cubePosition;
	_scale = size;

	// set the model transformations
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);
	_color = cubeColor;
	loadShaders(false);
	loadData();
}

// Create a cube with a texture
void Cube::create(const glm::vec3& cubePosition, const glm::vec3& size, std::vector<std::string> texturePaths)
{
	_position = cubePosition;
	_scale = size;

	// set the model transformations
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);

	if (texturePaths.size() == 1)
	{
		texture.createTexture(GL_CLAMP_TO_EDGE, GL_LINEAR, texturePaths[0]);
		loadShaders(true, std::map<const GLenum, const std::string>{ {GL_VERTEX_SHADER, "Shaders/sampler2DVS.glsl"}, { GL_FRAGMENT_SHADER, "Shaders/sampler2DFS.glsl" }});
	}
	else
	{
		texture.createCubeMap(GL_CLAMP_TO_EDGE, GL_LINEAR, texturePaths);
		loadShaders(true, std::map<const GLenum, const std::string>{{GL_VERTEX_SHADER, "Shaders/cubeMapVS.glsl"}, {GL_FRAGMENT_SHADER, "Shaders/cubeMapFS.glsl"}});
	}
	loadData();
}

// Update our view and projection matrix
void Cube::update(glm::mat4& view, glm::mat4& projection)
{
	this->view = view;
	this->projection = projection;

}

void Cube::setRotation(const float& angle, const glm::vec3& rotation)
{
	_rotation = rotation;
	_angle = angle;
	model = glm::rotate(model, _angle, rotation);
}

void Cube::move(const glm::vec3& position)
{
	_position = position;
	model = glm::translate(model, _position);
}

// Draw the object!
void Cube::render()
{
	// Set the active texture to render with, then bind it
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getTexture());
	glUniform1i(textureLocation, 0);

	// Bind our shaders for use
	shaders.use();

	// Send our uniform attributes to the GPU
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind the VAO, draw the object, then unbind the vao + shaders
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	shaders.unuse();

}

// Stores Vertex::Position/Color/UV
void Cube::loadData()
{
	// Vertex::Position data
	std::vector<glm::vec3> cubeData
	{        
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
	};
	// Texture UV Data
	std::vector<glm::vec2> UVs
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
	};
	// Create a temporary Vertex and add the data to our vertices container
	Vertex vert;
	vert.Color = _color;
	for(size_t i = 0; i < cubeData.size(); i++)
	{
		vert.Position = cubeData[i];
		vert.UV = UVs[i];
		vertices.push_back(vert);
	}
	loadBuffers();
}

// Override our Drawable::loadBuffers() function to not send any indices
void Cube::loadBuffers()
{
	glCreateVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

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