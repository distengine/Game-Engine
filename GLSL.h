#pragma once
#include <GL/glew.h>
#include <string>
#include <map>

class GLSL
{
public:
	GLSL();
	// add a shader to our mapp
	void addShader(GLenum shaderType, const std::string& shaderFilePath);

	// add an attribute into our shader
	void addAttribute(const std::string& attributeName);
	// returns the location of our uniforms
	GLint getUniformLocation(const std::string& uniformName) const;
	// add our shaders to our program
	void linkShaders();

	void use() const;
	void unuse() const;

	void deleteShaders();
private:
	// compile our files into shader code
	void compileShader(const std::string& shaderFilePath);
private:
	GLuint _programID;
	std::map<const std::string, GLuint> _shaders;
	int _numAttributes;
};
