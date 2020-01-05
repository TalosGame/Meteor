/*!
 * FileName: 	texture.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/28 20:36
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "texture.h"
#include "renderer.h"
#include "platform/opengl/opengl_texture.h"
 
__MTR_NS_BEGIN__

Ref<Texture2D> Texture2D::Create(float width, float height)
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path)
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(path);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

__MTR_NS_END__
