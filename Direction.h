#pragma once
#include "Drawable.h"
class Direction : public Drawable
{
public:
	// Create a line 
	void create(const glm::vec3& directionPosition, const glm::vec3& directionVector, const glm::vec3& color);
	// Update our view and projection matrix
	void update(glm::mat4& view, glm::mat4& projection);
	// Draw the object!
	void render();
private:
	void loadData();
	glm::vec3 _color;
};