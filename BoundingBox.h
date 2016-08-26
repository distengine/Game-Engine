#include "Drawable.h"
#include "Cube.h"

class BoundingBox : public Drawable
{
public:
	void create(const Cube& cube);
	// Update our view and projection matrix
	void update(glm::mat4& view, glm::mat4& projection);
	// Draw our bbox
	void render();
private:
	// Override our Drawable::loadBuffers() function to not send any indices
	void loadBuffers() override;
	void loadShaders(const bool& textured, std::map<const GLenum, const std::string> shaderTypes = std::map<const GLenum, const std::string> 
								{{GL_VERTEX_SHADER, "Shaders/sampler2DVS.glsl"},{GL_FRAGMENT_SHADER, "Shaders/sampler2DFS.glsl"}}) override;
	float _minX, _minY, _minZ, _maxX, _maxY, _maxZ;
};