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

void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array)
{
	glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->get_count(), GL_UNSIGNED_INT, nullptr);
}

__MTR_NS_END__
