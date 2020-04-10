/*!
 * FileName: 	opengl_shader.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/22 14:57
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_shader.h"
#include "meteor/core/path.h"

#include <fstream>
#include <glad/glad.h>
 
__MTR_NS_BEGIN__

static GLenum ShadeTypeFromString(const std::string& type) 
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;

	MTR_CORE_ASSERT(false, "Unknown shader type!");
	return 0;
}

OpenGLShader::OpenGLShader(const std::string& uri) 
{
	auto source = ReadShaderFile(uri);
	auto shaderSources = PreProcess(source);
	name_ = Path::GetFileName(uri);

	Compile(shaderSources);
}

OpenGLShader::OpenGLShader(const std::string& vert_src, const std::string& frag_src)
{
	std::unordered_map<GLenum, std::string> shaderSources;
	shaderSources[GL_VERTEX_SHADER] = vert_src;
	shaderSources[GL_FRAGMENT_SHADER] = frag_src;
	Compile(shaderSources);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(renderer_id_);
}

void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderScources) 
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	auto program = glCreateProgram();

	MTR_CORE_ASSERT(shaderScources.size() <= 2, "We only support 2 shader for now!");
	std::array<GLenum, 2> shader_ids_;
	int shader_index = 0;
	for (auto& kv : shaderScources)
	{
		 GLenum type = kv.first;
		 const std::string& source = kv.second;

		 GLuint shader = glCreateShader(type);
		 const GLchar *source_c = source.c_str();
		 glShaderSource(shader, 1, &source_c, 0);

		 // Compile the vertex shader
		 glCompileShader(shader);

		 GLint isCompiled = 0;
		 glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		 if (isCompiled == GL_FALSE)
		 {
			 GLint maxLength = 0;
			 glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			 // The maxLength includes the NULL character
			 std::vector<GLchar> infoLog(maxLength);
			 glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			 // We don't need the shader anymore.
			 glDeleteShader(shader);

			 MTR_ERROR("{0}", infoLog.data());
			 MTR_ASSERT(false, "Vertex shader compile error!");
			 break;
		 }

		 // Attach our shaders to our program
		 glAttachShader(program, shader);
		 shader_ids_[shader_index++] = shader;
	}

	renderer_id_ = program;

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
		for (auto id : shader_ids_)
		{
			glDeleteShader(id);
		}

		MTR_ERROR("{0}", infoLog.data());
		MTR_ASSERT(false, "OpenGLShader link error!");
		return;
	}

	// Don't leak shaders either.
	for (auto id : shader_ids_)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}

const std::string OpenGLShader::ReadShaderFile(const std::string& uri) 
{
	std::string result;
	std::ifstream in(uri, std::ios::in | std::ios::binary);
	if (!in) 
	{
		MTR_CORE_ERROR("Could not open file uri:{0}", uri);
		return nullptr;
	}

	in.seekg(0, std::ios::end);
	result.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&result[0], result.size());
	in.close();

	return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) 
{
	std::unordered_map<GLenum, std::string> shaderSources;

	const char* type_token = "#type";
	size_t type_token_len = strlen(type_token);
	size_t pos = source.find(type_token);

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		MTR_CORE_ASSERT(eol != std::string::npos, "syntax error");
		size_t begin = pos + type_token_len + 1;
		std::string type = source.substr(begin, eol - begin);
		MTR_CORE_ASSERT(ShadeTypeFromString(type), "Invalid shader type specified");

		size_t next_line_pos = source.find_first_not_of("\r\n", eol);
		MTR_CORE_ASSERT(next_line_pos != std::string::npos, "syntax error");
		pos = source.find(type_token, next_line_pos);

		shaderSources[ShadeTypeFromString(type)] = (pos == std::string::npos) ? source.substr(next_line_pos) : source.substr(next_line_pos, pos - next_line_pos);
	}

	return shaderSources;
}

void OpenGLShader::Bind()
{
	glUseProgram(renderer_id_);
}

void OpenGLShader::Unbind()
{
	glUseProgram(0);
}

void OpenGLShader::SetInt(const std::string& name, int value)
{
	UploadUniformInt(name, value);
}

void mtr::OpenGLShader::SetInts(const std::string& name, int* value, int count)
{
	UploadUniformInts(name, value, count);
}

void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	UploadUniformFloat3(name, value);
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	UploadUniformFloat4(name, value);
}

void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	UploadUniformMat4(name, value);
}

void OpenGLShader::UploadUniformInt(const std::string& name, int value)
{
	auto location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void mtr::OpenGLShader::UploadUniformInts(const std::string& name, int* value, int count)
{
	auto location = GetUniformLocation(name);
	glUniform1iv(location, count, value);
}

void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
{
	auto location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
	auto location = GetUniformLocation(name);
	glUniform2f(location, value.x, value.y);
}

void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
	auto location = GetUniformLocation(name);
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
	auto location = GetUniformLocation(name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	auto location = GetUniformLocation(name);
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
