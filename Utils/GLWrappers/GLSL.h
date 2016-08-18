#pragma once
#include <GL/glew.h>
#include <map>

namespace de
{
	enum class UniformType {
		UT_INT, UT_FLOAT, UT_VEC2, UT_VEC3, UT_VEC4, UT_MAT4
	};

	class GLSL
	{
	public:
		GLSL();
		~GLSL();
		// add a shader to our mapp
		void addShader(GLenum shaderType, const std::string& shaderFilePath);

		// add an attribute into our shader
		void addAttribute(const std::string& attributeName);
		// Sets the value of ints/floats/vecs/matrices
		template<typename T>
		void setValue(const std::string& name, UniformType type, T value);
		// returns the location of our uniforms
		GLint getUniformLocation(const std::string& uniformName) const;
		// add our shaders to our program
		void linkShaders();

		void deleteShaders();

		void use() const;
		void unuse() const;
	private:
		// compile our files into shader code
		void compileShader(const std::string& shaderFilePath);
	private:
		GLuint _programID;
		std::map<const std::string, GLuint> _shaders;
		int _numAttributes;
	};

	template<typename T>
	inline void GLSL::setValue(const std::string& name, UniformType type, T value)
	{
		switch (type)
		{
		case UniformType::UT_INT:
			glUniform1i(getUniformLocation(name), value);
			break;
		case UniformType::UT_FLOAT:
			glUniform1f(getUniformLocation(name), value);
			break;
		case UniformType::UT_VEC2:
			glUniform2f(getUniformLocation(name), value);
			break;
		case UniformType::UT_VEC3:
			glUniform3f(getUniformLocation(name), value);
			break;
		case UniformType::UT_VEC4:
			glUniform4f(getUniformLocation(name), value);
			break;
		case UniformType::UT_MAT4:
			glUniform4fv(getUniformLocation(name), value);
			break;
		}
	}
}