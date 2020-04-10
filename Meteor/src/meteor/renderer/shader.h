/*!
 * FileName: 	shader.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 11:11
 * Author: 		miller
 * Desc:
 */

#ifndef __MTR_SHADER_H__
#define __MTR_SHADER_H__

#include "mtrpch.h"
#include "meteor/core/core.h"

__MTR_NS_BEGIN__

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;

	virtual const std::string& GetName() const = 0;

	virtual void SetInt(const std::string& name, int value) = 0;
	virtual void SetInts(const std::string& name, int* value, int count) = 0;
	virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
	virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
	virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

	static Ref<Shader> Create(const std::string& uri);
	static Ref<Shader> Create(const std::string& vert_src, const std::string& frag_src);
};

class ShaderManager
{
public:
	static Ref<Shader> Load(const std::string& uri);
	static Ref<Shader> Get(const std::string& name);
private:
	static void Add(const std::string& name, const Ref<Shader>& shader);
	static bool IsExists(const std::string& name);
private:
	static std::unordered_map<std::string, Ref<Shader>> shaders_;
};

__MTR_NS_END__

#endif // __MTR_SHADER_H__
 
 
