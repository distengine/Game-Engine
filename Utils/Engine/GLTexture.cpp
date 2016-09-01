#include "GLTexture.h"
#include <SFML/Graphics/Image.hpp>

GLuint& GLTexture::createTexture(const GLenum& texWrap, const int& textureFiltering, const std::string filePath)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, texWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFiltering);

	sf::Image image;
	image.loadFromFile(filePath);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return _texture;
}

GLuint& GLTexture::createTexture(const int& wrapping, const int& filter, const texture2DAttribs tex2DAttribs)
{
	glGenTextures(1, &_texture);

	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexImage2D(tex2DAttribs.target, tex2DAttribs.level, tex2DAttribs.internalFormat, tex2DAttribs.width,
				 tex2DAttribs.height, tex2DAttribs.border, tex2DAttribs.format, tex2DAttribs.type, tex2DAttribs.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	return _texture;
}

GLuint& GLTexture::createCubeMap(const GLenum& texWrap, const int& textureFiltering, const std::vector<std::string> filePaths)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

	for(GLuint i = 0; i < filePaths.size(); i++)
	{
		sf::Image tempImage;
		tempImage.loadFromFile(filePaths[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, tempImage.getSize().x, tempImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage.getPixelsPtr());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, texWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, texWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, texWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, textureFiltering);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, textureFiltering);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return _texture;
}

void GLTexture::deleteTexture()
{
	glDeleteTextures(1, &_texture);
}

texture2DAttribs::texture2DAttribs(GLint cTarget, GLint cInternalFormat, GLsizei cWidth, GLsizei cHeight, GLenum cFormat, GLenum cType, GLvoid* cData, GLint cLevel, GLint cBorder)
{
	target = cTarget;
	level = cLevel;
	internalFormat = cFormat;
	width = cWidth;
	height = cHeight;
	border = cBorder;
	format = cFormat;
	type = cType;
	data = cData;
}