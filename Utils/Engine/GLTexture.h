#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

// This struct defines the attributes for glTexImage2D
struct texture2DAttribs
{
	texture2DAttribs(GLint cTarget, GLint cInternalFormat, GLsizei cWidth, GLsizei cHeight, GLenum cFormat, GLenum cType, GLvoid* cData, GLint cLevel = 0, GLint cBorder = 0);
	GLenum target;			// Specifies the texture target of which the most common are GL_TEXTURE_1D, GL_TEXTURE_2D and GL_TEXTURE_3D. 
	GLint level;			// Specifies the level-of-detail number. Level 0 is the base image level. Level n is the nth mipmap reduction image. 
	GLint internalFormat;	// Specifies the number of color components in the texture. 
	GLsizei width;			// Specifies the width of the texture image.
	GLsizei height;			// Specifies the height of the texture image, or the number of layers in a texture array.
	GLint border;	 		// This value must be 0.
	GLenum format;			// Specifies the format of the pixel data
	GLenum type;			// Specifies the data type of the pixel data.
	const GLvoid* data;		// Specifies a pointer to the image data in memory.
};

class GLTexture
{
public:
	GLuint& createTexture(const GLenum& texWrap, const int& textureFiltering, const std::string filePath);
	GLuint& createTexture(const int& wrapping, const int& filter, const texture2DAttribs tex2DAttribs);
	GLuint& createCubeMap(const GLenum& texWrap, const int& textureFiltering, const std::vector<std::string> filePaths);
	GLuint& getTexture() { return _texture; };
	void deleteTexture();
private:
	GLuint _texture;
};
