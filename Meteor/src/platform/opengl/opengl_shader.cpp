/*!
 * FileName: 	opengl_shader.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/22 14:57
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_shader.h"

#include <glad/glad.h>
 
__MTR_NS_BEGIN__

OpenGLShader::OpenGLShader(const std::string& vert_src, const std::string& frag_src)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar *source = vert_src.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		MTR_ERROR("{0}", infoLog.data());
		MTR_ASSERT(false, "Vertex shader compile error!");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar *)frag_src.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		MTR_ERROR("{0}", infoLog.data());
		MTR_ASSERT(false, "Fragment shader compile error!");
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	renderer_id_ = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(renderer_id_, vertexShader);
	glAttachShader(renderer_id_, fragmentShader);

	// Link our program
	glLinkProgram(renderer_id_);

	// Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
	GLint isLinked = 0;
	glGetProgramiv(renderer_id_, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(renderer_id_, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(renderer_id_, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(renderer_id_);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		MTR_ERROR("{0}", infoLog.data());
		MTR_ASSERT(false, "OpenGLShader link error!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(renderer_id_, vertexShader);
	glDetachShader(renderer_id_, fragmentShader);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(renderer_id_);
}

void mtr::OpenGLShader::Bind()
{
	glUseProgram(renderer_id_);
}

void OpenGLShader::Unbind()
{
	glUseProgram(0);
}

void mtr::OpenGLShader::UploadUniformInt(const std::string& name, int value)
{
	auto location = GetUniformLocation(name.c_str());
	glUniform1i(location, value);
}

void mtr::OpenGLShader::UploadUniformFloat(const std::string& name, float value)
{
	auto location = GetUniformLocation(name.c_str());
	glUniform1f(location, value);
}

void mtr::OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
	auto location = GetUniformLocation(name.c_str());
	glUniform2f(location, value.x, value.y);
}

void mtr::OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
	auto location = GetUniformLocation(name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void mtr::OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
	auto location = GetUniformLocation(name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	auto location = GetUniformLocation(name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

int32 OpenGLShader::GetUniformLocation(const std::string& name) const
{
	if (uniform_cache_.find(name) != uniform_cache_.end()) 
	{
		return uniform_cache_[name];
	}

	auto location = glGetUniformLocation(renderer_id_, name.c_str());
	uniform_cache_[name] = location;
	return location;
}

__MTR_NS_END__
