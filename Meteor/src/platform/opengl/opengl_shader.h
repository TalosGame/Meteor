/*!
 * FileName: 	opengl_shader.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/22 14:55
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_OPENGL_SHADER_H__
#define __MTR_OPENGL_SHADER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"
#include "meteor/renderer/shader.h"

typedef unsigned int GLenum;

__MTR_NS_BEGIN__

class OpenGLShader : public Shader
{
public:
	OpenGLShader(const std::string& uri);
	OpenGLShader(const std::string& vert_src, const std::string& frag_src);
	virtual ~OpenGLShader();

	virtual const std::string& GetName() const override { return name_; };

	virtual void Bind() override;
	virtual void Unbind() override;

	void UploadUniformInt(const std::string& name, int value);

	void UploadUniformFloat(const std::string& name, float value);
	void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
	void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
	void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

	void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	const std::string ReadShaderFile(const std::string& uri);
	std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
	void Compile(const std::unordered_map<GLenum, std::string>& shaderScources);

	int32 GetUniformLocation(const std::string& name) const;
private:
	uint32 renderer_id_;
	std::string name_;

	mutable std::unordered_map<std::string, int32> uniform_cache_;
};

__MTR_NS_END__

#endif // __MTR_OPENGL_SHADER_H__
