#pragma once
#include <string>
#include <vector>
#include <glm/mat4x2.hpp>
#include "../Graphics/Drawable.h"

enum class SkyBoxEnum{NightSky, Mountain};

class SkyBox : public Drawable
{
public:
	void setupSkyBox(std::vector<std::string> skyBoxStrings);
	void renderSkyBox();
	void releaseSkyBox();
	void update(glm::mat4& view, glm::mat4& projection);
private:
	void loadShaders();
};