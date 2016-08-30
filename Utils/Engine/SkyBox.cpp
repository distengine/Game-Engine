#include "SkyBox.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

void SkyBox::setupSkyBox(std::vector<std::string> skyBoxStrings)
{
	std::initializer_list<glm::vec3> skyboxVertices = {
		// Positions          
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
	};

	Vertex vert;
	for(auto& it : skyboxVertices)
	{
		vert.Position = it;
		vertices.push_back(vert);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex,Position)));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	loadShaders();
	texture.createCubeMap(GL_CLAMP_TO_EDGE, GL_LINEAR, skyBoxStrings);
}

void SkyBox::renderSkyBox()
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	shaders.use();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1i(shaders.getUniformLocation("skybox"), 0);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture.getTexture());
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	shaders.unuse();
}

void SkyBox::releaseSkyBox()
{
	glDeleteTextures(1, &texture.getTexture());
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	shaders.deleteShaders();
}

void SkyBox::update(glm::mat4& view, glm::mat4& projection)
{
	this->view = glm::mat4(glm::mat3(view));
	this->projection = projection;
}

void SkyBox::loadShaders()
{
	shaders.addShader(GL_VERTEX_SHADER, "Shaders/skyboxVertex.glsl");
	shaders.addShader(GL_FRAGMENT_SHADER, "Shaders/skyboxFragment.glsl");
	shaders.linkShaders();

	viewLoc = shaders.getUniformLocation("view");
	projLoc = shaders.getUniformLocation("projection");
}