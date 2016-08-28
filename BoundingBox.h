#include "Drawable.h"

class BoundingBox : public Drawable
{
public:
	void create(const std::vector<Vertex>& verts);
	// Update our view and projection matrix
	void update(const glm::mat4& m, glm::mat4& view, glm::mat4& projection);
	// Test collision on our bounding box
	bool testCollision(const BoundingBox& otherBox);
	// Draw our bbox
	void render();
private:
	// Override our Drawable::loadBuffers() function to not send any indices
	void loadBuffers() override;
	float _minX, _minY, _minZ, _maxX, _maxY, _maxZ;
	float _xPos, _yPos, _zPos;
	glm::vec3 _min, _max;
};