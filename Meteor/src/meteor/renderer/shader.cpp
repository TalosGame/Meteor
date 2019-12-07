/*!
 * FileName: 	shader.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 11:12
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "shader.h"

#include <glad/glad.h>
 
__MTR_NS_BEGIN__

Shader::Shader(const std::string& vert_src, const std::string& frag_src)
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

	// Note the different functions here: glGetProgram* instead of glGetShader*.
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
		MTR_ASSERT(false, "Shader link error!");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(renderer_id_, vertexShader);
	glDetachShader(renderer_id_, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(renderer_id_);
}

void mtr::Shader::bind()
{
	glUseProgram(renderer_id_);
}

void Shader::unbind()
{
	glUseProgram(0);
}

__MTR_NS_END__