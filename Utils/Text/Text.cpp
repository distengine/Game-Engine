#include "Text.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


void Text::create(GLfloat xPos, GLfloat yPos, const GLfloat& scale, const std::string& text, const glm::vec4& ortho, const glm::vec3& color)
{
	_xPos = xPos;
	_yPos = yPos;
	projection = glm::ortho(ortho.x, ortho.y, ortho.z, ortho.w);
	_text = text;
	_textColor = color;
	_scale = scale;
	loadShaders(false, std::map<const GLenum, const std::string>{{GL_VERTEX_SHADER, "Shaders/text.vs"},{GL_FRAGMENT_SHADER, "Shaders/text.fs"}} );
	loadBuffers();
}

void Text::setOrtho(const glm::vec4 & ortho)
{
	projection = glm::ortho(ortho.x, ortho.y, ortho.z, ortho.w);
}

void Text::setPosition(GLfloat xPos, GLfloat yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

void Text::render(FreeFont& font)
{
	GLfloat oldX = _xPos;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shaders.use();
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3f(shaders.getUniformLocation("textColor"), _textColor.r, _textColor.g, _textColor.b);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	for (auto& it : _text)
	{
		Character ch = font.characters[it];
		GLfloat xpos = _xPos + ch.Bearing.x * _scale;
		GLfloat ypos = _yPos - (ch.Size.y - ch.Bearing.y) * _scale;

		GLfloat w = ch.Size.x * _scale;
		GLfloat h = ch.Size.y * _scale;

		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		_xPos += (ch.Advance >> 6) * _scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	_xPos = oldX;
	glBindVertexArray(0);
	shaders.unuse();
}

void Text::loadBuffers()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}