/*!
 * FileName: 	vertex_array.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/08 20:21
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "vertex_array.h"
#include "renderer.h" 
#include "platform/opengl/opengl_vertex_array.h"

__MTR_NS_BEGIN__

VertexArray* VertexArray::create()
{
	switch (Renderer::GetApi())
	{
		case RendererAPI::API::None:		MTR_CORE_ASSERT(false, "RendererAPI::None type is wrong!") return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
	}

	MTR_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

__MTR_NS_END__
