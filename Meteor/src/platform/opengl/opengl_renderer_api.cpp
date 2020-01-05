/*!
 * FileName: 	opengl_renderer_api.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/15 15:58
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_renderer_api.h"
#include <glad/glad.h>

__MTR_NS_BEGIN__

void OpenGLRendererAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
{
	glViewport(x, y, width, height);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const mtr::Ref<VertexArray>& vertex_array)
{
	glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

__MTR_NS_END__
