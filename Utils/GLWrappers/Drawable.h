#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

#include "GLSL.h"


// A 'Point' for OpenGL
// Position, Color, TexCoords
struct Vertex
{
	Vertex();
	Vertex(glm::vec3 pos, glm::vec3 col, glm::vec2 uv = glm::vec2())
	{
		Position = pos;
		Color = col;
		TexCoords = uv;
	}
	glm::vec3 Position, Color;
	glm::vec2 TexCoords;
};
namespace de {
	// This is a base class for all OpenGL drawable objects in a 3D space
	class Drawable
	{
	public:
		Drawable();
		virtual ~Drawable();

		virtual void loadData();
		virtual void loadShaders();
		virtual void loadBuffers();
		virtual void update();
		virtual void render();

		GLuint vao, vbo, ebo;

		glm::mat4 model, view, projection;
		GLint modelLoc, viewLoc, projLoc;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;

		de::GLSL shaders;
	};
}