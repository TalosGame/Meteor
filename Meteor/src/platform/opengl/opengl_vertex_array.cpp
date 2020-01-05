/*!
 * FileName: 	opengl_vertex_array.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/12/14 16:21
 * Author: 		miller
 * Desc:
 */

#include "mtrpch.h"
#include "opengl_vertex_array.h"

#include <Glad/glad.h>
 
__MTR_NS_BEGIN__

static GLenum ShaderDataType2OGLType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::Float2:   return GL_FLOAT;
	case ShaderDataType::Float3:   return GL_FLOAT;
	case ShaderDataType::Float4:   return GL_FLOAT;
	case ShaderDataType::Mat3:     return GL_FLOAT;
	case ShaderDataType::Mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Int2:     return GL_INT;
	case ShaderDataType::Int3:     return GL_INT;
	case ShaderDataType::Int4:     return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}

	MTR_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &renderer_id_);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &renderer_id_);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(renderer_id_);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const mtr::Ref<VertexBuffer>& vertex_buffer)
{
	glBindVertexArray(renderer_id_);
	vertex_buffer->Bind();

	const auto& layout = vertex_buffer->layout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(vertext_buffer_index_);
		glVertexAttribPointer(vertext_buffer_index_,
							  element.GetComponentCount(),
							  ShaderDataType2OGLType(element.type_),
							  element.normalized_ ? GL_TRUE : GL_FALSE,
							  layout.stride(),
							  (const void*)element.offset_);

		vertext_buffer_index_++;
	}

	vertext_buffers_.push_back(vertex_buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const mtr::Ref<IndexBuffer>& index_buffer)
{
	glBindVertexArray(renderer_id_);
	index_buffer->Bind();

	index_buffer_ = index_buffer;
}

__MTR_NS_END__