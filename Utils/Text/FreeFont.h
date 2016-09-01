#pragma once

#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <map>
#include <freetype/config/ftheader.h>
#include FT_FREETYPE_H

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class FreeFont
{
public:
	void loadFont(const std::string& fontPath, const int& fontSize);
	int fontSize;
	std::map<GLchar, Character> characters;
};