#include "GLSL.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


de::GLSL::GLSL(): _programID(0), _numAttributes(0)
{
}

de::GLSL::~GLSL()
{
	//We don't need the program anymore.
	glDeleteProgram(_programID);
	//Don't leak shaders either.
	for (auto& it : _shaders)
	{
		glDeleteShader(it.second);
	}
}


void de::GLSL::addShader(GLenum shaderType, const std::string& shaderFilePath)
{
	// if no program is created, make one.
	if(_programID == 0)
	{
		_programID = glCreateProgram();
	}
	// create our shader
	auto tempID = glCreateShader(shaderType);
	_shaders.insert(std::pair<const std::string&,GLuint>(shaderFilePath, tempID));
	// make sure our shader was created successfully
	if(_shaders.at(shaderFilePath) == 0)
	{
		std::cout << "Could not create " << shaderFilePath  << std::endl;
	}
	// compile each shader
	compileShader(shaderFilePath);
}

void de::GLSL::compileShader(const std::string& shaderFilePath)
{
	// load our file into a stream and store it into a string
	std::ifstream fileStream(shaderFilePath);
	if(!fileStream.is_open())
	{
		std::cout << "Could not open" << shaderFilePath << std::endl;
	}

	std::string fileContents = "";
	std::string line;

	while(std::getline(fileStream,line))
	{
		fileContents += line + "\n";
	}
	// close our file so it doesn't leak
	fileStream.close();

	const char* filePtr = fileContents.c_str();
	// create a shader using our fileContents as the source
	glShaderSource(_shaders.at(shaderFilePath), 1, &filePtr, nullptr);

	glCompileShader(_shaders.at(shaderFilePath));

	// check for errors
	GLint success = 0;
	glGetShaderiv(_shaders[shaderFilePath], GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(_shaders[shaderFilePath], GL_INFO_LOG_LENGTH, &maxLength);
		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(_shaders[shaderFilePath], maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		//Exit with failure.
		glDeleteShader(_shaders[shaderFilePath]); //Don't leak the shader.

		//Print error log and quit
		std::printf("%s\n", &(errorLog[0]));
		std::cout << "Shader " + shaderFilePath + " failed to compile" << std::endl;
	}
}

//Adds an attribute to our shader. Should be called between compiling and linking.
void de::GLSL::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint de::GLSL::getUniformLocation(const std::string& uniformName) const
{
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		std::cout << "Uniform " + uniformName + " not found in shader!" << std::endl;
	}
	return location;
}

void de::GLSL::use() const
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void de::GLSL::unuse() const
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void de::GLSL::linkShaders()
{
	// attach our shaders to the program
	for(auto& it : _shaders)
	{
		glAttachShader(_programID, it.second);
	}

	//Link our program
	glLinkProgram(_programID);
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		deleteShaders();

		//print the error log and quit
		std::printf("%s\n", &(errorLog[0]));
		std::cout << "Shaders failed to link!" << std::endl;
	}
	for(auto& it : _shaders)
	{
		glDetachShader(_programID, it.second);
		glDeleteShader(it.second);
	}
}

void de::GLSL::deleteShaders()
{
	//We don't need the program anymore.
	glDeleteProgram(_programID);
	//Don't leak shaders either.
	for (auto& it : _shaders)
	{
		glDeleteShader(it.second);
	}
}
