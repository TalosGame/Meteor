/*!
 * FileName: 	buffer.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/07 13:11
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "buffer.h"
#include "renderer.h"
#include "platform/opengl/opengl_buffer.h"

__MTR_NS_BEGIN__

Ref<VertexBuffer> VertexBuffer::Create(float * vertices, uint64 size)
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32 * indices, uint32 count)
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

__MTR_NS_END__