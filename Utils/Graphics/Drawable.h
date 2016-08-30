#pragma once

// Distend
#include "GLSL.h"
#include "../Engine/GLTexture.h"

// GL and glm
#include <GL/glew.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>

// Std
#include <vector>
#include <glm/detail/type_vec2.hpp>

// A structure to define each vertex of a model
struct Vertex
{
	glm::vec3 Position, Color;
	glm::vec2 UV;
};

// Our base class for all our drawable objects
class Drawable
{
public:
	Drawable();
	// cleans up our shaders, textures, and buffers
	virtual ~Drawable();

	// loads the buffers and shaders for our drawable
	virtual void loadBuffers();
	virtual void loadShaders(const bool& textured, std::map<const GLenum, const std::string> shaderTypes =
		std::map<const GLenum, const std::string>{
	{GL_VERTEX_SHADER, "Shaders/vertexShader.glsl"},
	{GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl"}});
	// Shader object
	GLSL shaders;
	
	// Containers for vertex data and indices
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	// Shader Uniforms
	glm::mat4 model, view, projection;
	GLint modelLoc, viewLoc, projLoc, textureLocation;

	// Buffer objects
	GLuint vao, vbo, ebo;

	// GLTexture
	GLTexture texture;
};