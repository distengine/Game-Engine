#include "FreeFont.h"
#include <GL/glew.h>
#include <iostream>
#include <string>
#include "../Engine/GLTexture.h"

void FreeFont::loadFont(const std::string & fontPath, const int& fontSize)
{
	this->fontSize = fontSize;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Could not Init Free Type" << std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
	{
		std::cout << "Failed to load font: " << fontPath << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load Character Glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Failed to load Glyph" << std::endl;
		}

		// Generate Texture
		GLTexture tempTexture;
		tempTexture.createTexture(GL_CLAMP_TO_EDGE, GL_LINEAR, texture2DAttribs(GL_TEXTURE_2D, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer));
		Character character
		{
			tempTexture.getTexture(),
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.emplace(c, character);
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}
