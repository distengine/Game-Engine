#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "FreeFont.h"
#include "../Graphics/Drawable.h"

class Text : public Drawable
{
public:
	void create(GLfloat xPos, GLfloat yPos, const GLfloat& scale, const std::string& text, const glm::vec4& ortho, const glm::vec3& color);
	void setOrtho(const glm::vec4& ortho);
	void setPosition(GLfloat xPos, GLfloat yPos);
	void render(FreeFont& font);
private:
	void loadBuffers() override;

	std::string _text;
	glm::vec3 _textColor;
	GLfloat _scale;
	GLfloat _xPos, _yPos;
};
