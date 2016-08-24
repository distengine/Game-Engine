#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

class GLTexture
{
public:
	GLuint& createTexture(const GLenum& texWrap, const int& textureFiltering, const std::string filePath);
	GLuint& createCubeMap(const GLenum& texWrap, const int& textureFiltering, const std::vector<std::string> filePaths);
	GLuint& getTexture() { return _texture; };
	void deleteTexture();
private:
	GLuint _texture;
};
