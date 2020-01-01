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

#include "renderer.h"
#include "platform/opengl/opengl_shader.h"

__MTR_NS_BEGIN__
Ref<Shader> Shader::Create(const std::string& uri) 
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(uri);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<Shader> Shader::Create(const std::string& vert_src, const std::string& frag_src) 
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLShader>(vert_src, frag_src);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

/// Shader Manager/////////////////////////////////////////////////////////////////
std::unordered_map<std::string, Ref<Shader>> ShaderManager::shaders_;

Ref<Shader> ShaderManager::Load(const std::string& uri)
{
	auto shader = Shader::Create(uri);
	Add(shader->GetName(), shader);
	return shader;
}

Ref<Shader> ShaderManager::Get(const std::string& name)
{
	MTR_CORE_ASSERT(IsExists(name), "Shader not found! name:{0}", name);
	return shaders_[name];
}

void ShaderManager::Add(const std::string& name, const Ref<Shader>& shader)
{
	MTR_CORE_ASSERT(!IsExists(name), "Shader already exists!");
	shaders_[name] = shader;
}

bool ShaderManager::IsExists(const std::string& name) 
{
	return shaders_.find(name) != shaders_.end();
}
__MTR_NS_END__
