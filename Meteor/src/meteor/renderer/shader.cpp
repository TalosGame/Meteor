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

Shader* Shader::Create(const std::string& vert_src, const std::string& frag_src) 
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vert_src, frag_src);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

__MTR_NS_END__