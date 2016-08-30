#pragma once
#include "../Drawable.h"

// Cube is a drawable object
class Cube : public Drawable
{
public:
	// Create a cube with a color
	void create(const glm::vec3& cubePosition, const glm::vec3& size, const glm::vec3& cubeColor);
	// Create a cube with a texture
	void create(const glm::vec3& cubePosition, const glm::vec3& size, std::vector<std::string> texturePaths);
	// Update our view and projection matrix
	void update(glm::mat4& view, glm::mat4& projection);
	// Update our rotation
	void setRotation(const float& angle ,const glm::vec3& rotation);
	// Update our position
	void move(const glm::vec3& position);
	// Draw the object!
	void render();
private:
	// Stores Vertex::Position/Color/UV
	void loadData();
	// Override our Drawable::loadBuffers() function to not send any indices
	void loadBuffers() override;
	// Store the cube' color, and transformations
	glm::vec3 _color, _scale, _position, _rotation;
	float _angle;
};